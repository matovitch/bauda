#include "command/signin.hpp"

#include <string>

#include <nlohmann/json.hpp>

#include "command/cmd_abstract.hpp"
#include "command/cmd_name.hpp"
#include "interface/reply.hpp"
#include "common/status.hpp"

const std::string Signin::name() const { return CMD_NAME_SIGNIN; }

Signin::Signin(const std::string& username) : 
    CmdAbstract(username)
{
    CmdAbstract::init();
}

const nlohmann::json Signin::operator()(const std::string& password,
                                        const std::string& email)
{
    return reply::buildServerReplyAsJson(Status::KO_NOT_YET_IMPLEMENTED);
}