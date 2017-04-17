#include "command/signin.hpp"

#include <string>

#include <nlohmann/json.hpp>

#include "command/cmd_abstract.hpp"
#include "database/database.hpp"
#include "command/cmd_name.hpp"
#include "interface/reply.hpp"
#include "common/status.hpp"
#include "capnp/user.hpp"

const std::string Signin::name() const { return K_CMD_NAME_SIGNIN; }

Signin::Signin(const std::string& username) : 
    CmdAbstract(username)
{
    CmdAbstract::init();
}

const nlohmann::json Signin::operator()(const std::string& password,
                                        const std::string& email)
{
    auto& userDb = database::get(Config::get()["database"]["user"]);

    if (!userDb.isNotFound(getUserIdAsString()))
    {
        return reply::buildServerReplyAsJson(Status::KO_SIGNIN_USERNAME_TAKEN, logger());
    }

    if (!userDb.set(getUserIdAsString(), user::create(getUsername(), password, email)))
    {
        return reply::buildServerReplyAsJson(Status::KO_SIGNIN_DATABASE_ERROR, logger());
    }

    return reply::buildServerReplyAsJson(Status::OK, logger());
}