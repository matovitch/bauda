#include "command/login.hpp"

#include <string>

#include <nlohmann/json.hpp>

#include "command/cmd_abstract.hpp"
#include "command/cmd_name.hpp"
#include "interface/reply.hpp"
#include "common/status.hpp"

const std::string Login::name() const { return CMD_NAME_LOGIN; }

Login::Login(const std::string& username) : 
    CmdAbstract(username)
{
    CmdAbstract::init();
}

const nlohmann::json Login::operator()(const std::string& password)
{
    return reply::buildServerReplyAsJson(Status::KO_NOT_YET_IMPLEMENTED);
}