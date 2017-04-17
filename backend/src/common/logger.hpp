#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

namespace logger
{
    enum Level
    {
        DEBUG,
        INFO,
        WARN,
        ERROR,
        CRITICAL
    };

    typedef std::shared_ptr<spdlog::logger> Logger;

    void init();

    void cleanRegister();

    Logger create(const std::string& name);

    Logger get(const std::string& name);

    const std::string dumpJson(const nlohmann::json& json);

    template <typename... Args>
    void write(const std::shared_ptr<spdlog::logger> log, 
               const Level level, 
               const std::string& format, 
               Args... args)
    {
        const auto fullFormatAsString = "<{}:{}> " + format;
        const auto fullFormatAsCStr   = fullFormatAsString.c_str();

        if (level == Level::DEBUG)
        {
            log->debug(fullFormatAsCStr, args...);
        }
        else 
        if (level == Level::INFO)
        {            
            log->info(fullFormatAsCStr, args...);
        }
        else 
        if (level == Level::WARN)
        {
            log->warn(fullFormatAsCStr, args...);
        }
        else 
        if (level == Level::ERROR)
        {
            log->error(fullFormatAsCStr, args...);
        }
        else 
        if (level == Level::CRITICAL)
        {
            log->critical(fullFormatAsCStr, args...);
        }
    }

} // end logger namespace

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"

#define MY_LOG_DEBUG(log, format, ...)    logger::write(log, logger::Level::DEBUG   , format, __FILE__, __LINE__, ##__VA_ARGS__)
#define MY_LOG_INFO(log, format, ...)     logger::write(log, logger::Level::INFO    , format, __FILE__, __LINE__, ##__VA_ARGS__)
#define MY_LOG_WARN(log, format, ...)     logger::write(log, logger::Level::WARN    , format, __FILE__, __LINE__, ##__VA_ARGS__)
#define MY_LOG_ERROR(log, format, ...)    logger::write(log, logger::Level::ERROR   , format, __FILE__, __LINE__, ##__VA_ARGS__)
#define MY_LOG_CRITICAL(log, format, ...) logger::write(log, logger::Level::CRITICAL, format, __FILE__, __LINE__, ##__VA_ARGS__)

#pragma clang diagnostic pop

class Loggable
{

public:

    void init(const std::string& loggerName);

    const logger::Logger& logger() const;

private:

    logger::Logger _logger;
};

#endif // end __LOGGER_H__