#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <boost/filesystem.hpp>
#include <nlohmann/json.hpp>
#include <fstream>
#include <chrono>

class Config
{

public:

    static const nlohmann::json& get();

    static boost::filesystem::path path;

private:

    static std::chrono::system_clock::time_point _lastUpdate;
    static nlohmann::json                        _conf;
};

#endif // end __CONFIG_H__