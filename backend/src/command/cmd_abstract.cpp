#include "command/cmd_abstract.hpp"

#include <functional>

#include <fmt/format.h>

#include "common/logger.hpp"

CmdAbstract::CmdAbstract(const std::string& username) :
    _username(username),
    _userid(std::hash<std::string>{}(username))
    
{}

void CmdAbstract::init()
{
    Loggable::init(fmt::format("{:=16x} - {}", getUserid(), name()));
    LOG_DEBUG(logger(), "Starting command.");
}

const std::string& CmdAbstract::getUsername()
{
    return _username;
}

const uint64_t CmdAbstract::getUserid()
{
    return _userid;
}