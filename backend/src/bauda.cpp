
#include <boost/range/combine.hpp>
#include <boost/foreach.hpp>
#include <functional>
#include <iostream>
#include <memory>
#include <thread>
#include <random>
#include <vector>

#include "conf_reader.hpp"
#include "uWS.h"

int main(int argc, const char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Wrong number of argument. (expecting 1)" << std::endl;
        return 0;
    }

    ConfReader confReader(argv[1]);

    uWS::EventSystem es(uWS::MASTER);
    uWS::Server      master(es);

    std::vector<std::unique_ptr<std::thread>> threads;
    std::vector<std::unique_ptr<uWS::Server>> workers;

    const std::size_t nbOfThreads = confReader()["websockets"]["threads"];

    workers.reserve(nbOfThreads);
    threads.reserve(nbOfThreads);

    auto generator = std::default_random_engine(std::random_device()());
    std::uniform_int_distribution<std::size_t> distribution(0, workers.size() - 1);

    master.onUpgrade
    (
        [&workers, &distribution, &generator](uv_os_fd_t fd,
                                              const char* secKey, 
                                              void* ssl, 
                                              const char* extensions,
                                              size_t extensionsLength)
        {
            workers[distribution(generator)]->upgrade(fd,
                                                      secKey,
                                                      ssl,
                                                      extensions,
                                                      extensionsLength);
        }
    );

    for (std::size_t i = 0; i < workers.size(); i++)
    {
        auto& worker = workers[0];
        auto& thread = threads[0];

        thread = 
            std::make_unique<std::thread>
            (
                [&worker, &confReader]()
                {
                    uWS::EventSystem tes(uWS::WORKER);
                    worker = std::make_unique<uWS::Server>
                        (
                            tes,
                            confReader()["websockets"]["port"], 
                            confReader()["websockets"]["options"], 
                            confReader()["websockets"]["max_payload"]
                        );

                    worker->onConnection
                    (
                        [](uWS::WebSocket socket)
                        {
                            std::cout << "[Connection] clients: " << std::endl;
                        }
                    );

                    worker->onMessage
                    (
                        [](uWS::WebSocket socket, const char* message, size_t length, uWS::OpCode opCode)
                        {
                            std::cout << std::string(message).substr(0, length) << std::endl;
                            socket.send(message, length, opCode);
                        }
                    );

                    worker->onDisconnection
                    (
                        [](uWS::WebSocket socket, int code, char *message, size_t length)
                        {
                            std::cout << "[Disconnection] clients: " << std::endl;
                        }
                    );
                    tes.run();
                }
            );
    }

    es.run();

    return 0;
}