#include <exception>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

#include <boost/filesystem.hpp>
#include <nlohmann/json.hpp>
#include <uWS/uWS.h>

#include "database/database.hpp"
#include "interface/reply.hpp"
#include "common/config.hpp"
#include "common/logger.hpp"
#include "utils/uws.hpp"

int main(int argc, const char** argv)
{
    if (argc != 2)
    {
        std::cerr << "ERROR: Expecting path to configuration file." << std::endl;
        return 0;
    }

    Config::path = boost::filesystem::path{argv[1]};

    logger::init();

    auto mainLogger = logger::create(Config::get()["log"]["main_logger"]);

    MY_LOG_INFO(mainLogger, "####################################");
    MY_LOG_INFO(mainLogger, "#      CREATE/OPEN DATABASES       #");
    MY_LOG_INFO(mainLogger, "####################################");

    database::create(Config::get()["database"]["user"]);

    MY_LOG_INFO(mainLogger, "####################################");
    MY_LOG_INFO(mainLogger, "#      START WEBSOCKET SERVER      #");
    MY_LOG_INFO(mainLogger, "####################################");

    uWS      ::Hub          master;
    uWS_utils::TheadedHubs workers;

    workers.resize(Config::get()["websocket"]["workers_size"]);

    master.onConnection
    (
        [&](uWS::WebSocket<uWS::SERVER> webSocket, 
            uWS::UpgradeInfo upgradeInfo)
        {
            MY_LOG_INFO(mainLogger,"Connection on master uWS::Hub, forward to workers.");
            webSocket.transfer(uWS_utils::pickDefaultGroup(workers));
        }
    );

    for (auto& worker : workers)
    {
        worker.thread = std::make_unique<std::thread>
        (
            [&worker]()
            {
                worker.hub = std::make_unique<uWS::Hub>();
                auto& hub = *(worker.hub);
                
                hub.onMessage
                (
                    [](uWS::WebSocket<uWS::SERVER> webSocket, char* msg, size_t length, uWS::OpCode code)
                    {
                        auto mainLogger = logger::get(Config::get()["log"]["main_logger"]);

                        nlohmann::json msgAsJson;

                        try
                        {
                            msgAsJson = nlohmann::json::parse(std::string{msg, length});
                        } 
                        catch (const std::invalid_argument& invalid_argument)
                        {
                            MY_LOG_ERROR(mainLogger, 
                                      "[EXCEPTION] Invalid message({} bytes): {}",
                                      length,
                                      invalid_argument.what());
                            MY_LOG_DEBUG(mainLogger, 
                                      "[EXCEPTION] Message:\n{}",
                                      msg);
                        }

                        MY_LOG_DEBUG(mainLogger, "Receiving:\n{}", logger::dumpJson(msgAsJson));

                        const auto& reply = reply::asString(msgAsJson);

                        MY_LOG_DEBUG(mainLogger, "Replying:\n{}", logger::dumpJson(nlohmann::json::parse(reply)));

                        webSocket.send(reply.c_str(), reply.size(), code);
                    }
                );
                
                hub.getDefaultGroup<uWS::SERVER>().addAsync();
                hub.run();
            }
        );
    }

    master.getDefaultGroup<uWS::SERVER>().addAsync();
    master.listen(Config::get()["websocket"]["port"]);
    master.run();

    return 0;
}
