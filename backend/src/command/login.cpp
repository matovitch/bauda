#include "command/login.hpp"

#include <string>

#include <nlohmann/json.hpp>

#include "command/cmd_abstract.hpp"
#include "database/database.hpp"
#include "command/cmd_name.hpp"
#include "interface/reply.hpp"
#include "common/status.hpp"
#include "capnp/user.hpp"

const std::string Login::name() const { return K_CMD_NAME_LOGIN; }

Login::Login(const std::string& username) : 
    CmdAbstract(username)
{
    CmdAbstract::init();
}

const nlohmann::json Login::operator()(const std::string& password)
{
    auto& userDb = database::get(Config::get()["database"]["user"]);

    auto userBlob = userDb.get(getUserIdAsString());

    if (!userBlob)
    {
        return reply::buildServerReplyAsJson(Status::KO_LOGIN_USER_NOT_FOUND);
    }

    if (!user::checkPassword(*userBlob, password))
    {
        return reply::buildServerReplyAsJson(Status::KO_LOGIN_WRONG_PASSWORD);
    }

    return reply::buildServerReplyAsJson(Status::OK);
}