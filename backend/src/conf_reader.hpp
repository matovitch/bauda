#ifndef __CONF_READER_H__
#define __CONF_READER_H__

#include <boost/filesystem.hpp>
#include <fstream>
#include <chrono>

#include "json.hpp"

struct ConfReader
{
    ConfReader(const char* pathAsConstCharPtr) :
        _path(pathAsConstCharPtr)
    {
        operator()();
    }

    nlohmann::json operator()()
    {
        if (!boost::filesystem::exists         (_path) ||
            !boost::filesystem::is_regular_file(_path))
        {
            throw std::runtime_error("Path to global configuration file is invalid.");
        }

        std::chrono::system_clock::time_point lastWrite
            (
                std::chrono::system_clock::from_time_t
                (
                    boost::filesystem::last_write_time(_path)
                )
            );

        if (_lastUpdate < lastWrite)
        {
            _lastUpdate = lastWrite;
            std::ifstream ifstream(_path.string(), std::ifstream::in);
            std::stringstream sstream;
            sstream << ifstream.rdbuf();

            _conf = nlohmann::json::parse(sstream.str());
        }

        return _conf;
    }

    std::chrono::system_clock::time_point _lastUpdate;
    boost::filesystem::path               _path;
    nlohmann::json                        _conf;
};

#endif