#include "common/logger.hpp"

#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <string>

#include "common/config.hpp"

namespace logger
{
    typedef std::unordered_map<std::shared_ptr<spdlog::logger>, 
                               std::chrono::system_clock::time_point> LoggerRegister;

    static LoggerRegister loggerRegister;
    static std::chrono::system_clock::time_point lastClean;

    void init()
    {
        spdlog::set_async_mode(Config::get()["log"]["queue_size"],
                               spdlog::async_overflow_policy::block_retry,
                               nullptr,
                               std::chrono::milliseconds(Config::get()["log"]["flush_delay_in_ms"]));

        spdlog::set_level(Config::get()["debug_mode"] ? spdlog::level::debug 
                                                          : spdlog::level::info);

        lastClean = std::chrono::system_clock::now();
    }

    std::shared_ptr<spdlog::logger> create(const std::string& name)
    {
        if (spdlog::get(name))
        {
            return spdlog::get(name);
        }

        const std::string rootPath = Config::get()["root_path"];
        const std::string  logPath = Config::get()["log"]["path"];

        auto logger = spdlog::basic_logger_mt(name, 
                                              rootPath + logPath);

        if (name != Config::get()["log"]["main_logger"])
        {
            loggerRegister[logger] = std::chrono::system_clock::now();
        }

        std::size_t cleanPeriod = Config::get()["log"]["clean_period"];

        if (!(loggerRegister.size() % cleanPeriod) &&
            !(loggerRegister.empty()))
        {
            cleanRegister();
        }

        return logger;
    }

    void cleanRegister()
    {
        const auto& now = std::chrono::system_clock::now();
        const auto& loggersLifespan = 
            std::chrono::seconds(Config::get()["log"]["loggers_lifespan"]);

        auto it = loggerRegister.begin();

        while (it != loggerRegister.end())
        {
            if (now - it->second > loggersLifespan)
            {
                spdlog::drop(it->first->name());

                LOG_DEBUG(get(Config::get()["log"]["main_logger"]),
                          "Logger {} expired.", it->first->name());

                it = loggerRegister.erase(it);
            }
            else
            {
                it++;
            }
        }
    }

    std::shared_ptr<spdlog::logger> get(const std::string log)
    {
        return spdlog::get(log);
    }

    const std::string dumpJson(const nlohmann::json& json)
    {
        return json.dump(Config::get()["log"]["json_indent"]);
    }
} // end logger namespace


void Loggable::init(const std::string& loggerName)
{
    _logger = logger::create(loggerName);
}

const std::shared_ptr<spdlog::logger> Loggable::logger() const { return _logger; }