#include "config.hpp"

#include <boost/filesystem.hpp>
#include <nlohmann/json.hpp>
#include <chrono>

boost::filesystem::path               Config::path;
std::chrono::system_clock::time_point Config::_lastUpdate;
nlohmann::json                        Config::_conf;

const nlohmann::json& Config::get()
{
    if (!boost::filesystem::exists         (path) ||
        !boost::filesystem::is_regular_file(path))
    {
        throw std::runtime_error("Path to global configuration file is invalid.");
    }

    std::chrono::system_clock::time_point lastWrite
    (
        std::chrono::system_clock::from_time_t
        (
            boost::filesystem::last_write_time(path)
        )
    );

    if (_conf.empty() || _lastUpdate < lastWrite)
    {
        _lastUpdate = lastWrite;
        std::ifstream ifstream(path.string(), std::ifstream::in);
        std::stringstream sstream;
        sstream << ifstream.rdbuf();

        _conf = nlohmann::json::parse(sstream.str());
    }

    return _conf;
}