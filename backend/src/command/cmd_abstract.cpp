#include "command/cmd_abstract.hpp"

#include <functional>

#include <fmt/format.h>

#include "common/logger.hpp"

extern "C"
{
    #include "utils/xxhash.h"
}

CmdAbstract::CmdAbstract(const std::string& username) :
    _username(username) 
{}

void CmdAbstract::init()
{
    Loggable::init(fmt::format("{} - {}", getUserIdAsString(), name()));
    MY_LOG_DEBUG(logger(), "Starting command.");
}

const std::string& CmdAbstract::getUsername() const
{
    return _username;
}

const uint64_t CmdAbstract::getUserId() const
{
    return XXH64(_username.c_str(), _username.size(), 0);
}

const std::string CmdAbstract::getUserIdAsString() const
{
    return fmt::format("{:=16x}", getUserId());
}


