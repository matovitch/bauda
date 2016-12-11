#include "interface/reply.hpp"

#include <string>

#include <nlohmann/json.hpp>

#include "command/cmd_name.hpp"
#include "command/signin.hpp"
#include "common/logger.hpp"
#include "common/config.hpp"
#include "utils/json.hpp"

namespace reply
{

const std::string asString(nlohmann::json& query)
{
    auto mainLogger = logger::get(Config::get()["log"]["main_logger"]);

    auto model       = json_utils::getFrom(query, "model"       , json_utils::asObject);
    auto serverQuery = json_utils::getFrom(query, "server_query", json_utils::asString);

    if (!model)
    {
        LOG_WARN(mainLogger, "No model found in query. Replying an error.");
        return buildFromStatus(query, Status::KO_NO_MODEL);
    }

    if (!serverQuery)
    {
        LOG_WARN(mainLogger, "No server_query found in query. Replying an error.");
        return buildFromStatus(query, Status::KO_NO_SERVER_QUERY);
    }

    return buildFromJson
           (
               query,
               serverReply(*serverQuery, *model)
           );
}

const nlohmann::json serverReply(const std::string& serverQuery, 
                                 const nlohmann::json& model)
{

    auto username = json_utils::getFrom(model, "username", json_utils::asString);

    if (!username)
    {
        LOG_WARN(logger::get(Config::get()["log"]["main_logger"]),
                 "No username found in model. Replying an error.");

        return buildServerReplyAsJson(Status::KO_NO_USERNAME);
    }

    auto userId     = std::hash<std::string>{}(*username);
    auto userLogger = logger::create(fmt::format("{:=16x}", userId));

    LOG_INFO(userLogger, "Proccessing server query of type <{}>", serverQuery);

    if (serverQuery == CMD_NAME_LOGIN)
    {
        return buildLoginReply(*username, model);
    }
    if (serverQuery == CMD_NAME_SIGNIN)
    {
        return buildSigninReply(*username, model);
    }

    return buildServerReplyAsJson(Status::KO_UNKNOWN_SERVER_QUERY);
}

const nlohmann::json buildLoginReply(const std::string& username,
                                     const nlohmann::json& model)
{
    return buildServerReplyAsJson(Status::KO_NOT_YET_IMPLEMENTED);
}

const nlohmann::json buildSigninReply(const std::string& username,
                                      const nlohmann::json& model)
{
    auto mainLogger = logger::get(Config::get()["log"]["main_logger"]);

    auto secret = json_utils::getFrom(model, "secret", json_utils::asObject);
    auto email  = json_utils::getFrom(model, "email" , json_utils::asString);

    if (!secret)
    {
        LOG_WARN(mainLogger, "No secret found in model. Replying an error.");
        return buildServerReplyAsJson(Status::KO_NO_SECRET);
    }

    if (!email)
    {
        LOG_WARN(mainLogger, "No email found in model. Replying an error.");
        return buildServerReplyAsJson(Status::KO_NO_EMAIL);
    }

    auto password = json_utils::getFrom(*secret, "password", json_utils::asString);

    if (!password)
    {
        LOG_WARN(mainLogger, "No password found in model. Replying an error.");
        return buildServerReplyAsJson(Status::KO_NO_PASSWORD);
    }

    return Signin{username}(*password, *email);
}

nlohmann::json buildServerReplyAsJson(const Status& status,
                                      const nlohmann::json& data)
{
    auto server_reply = EMPTY_SERVER_REPLY;

    server_reply["status_code"]        = status.getCode();
    server_reply["status_description"] = status.getDescription();
    server_reply["data"]               = data; 

    return server_reply;
}

const std::string buildFromJson(nlohmann::json& query,
                                const nlohmann::json& serverReply)
{
    query["server_reply"] = serverReply;
    return query.dump();
}

const std::string buildFromStatus(nlohmann::json& query,
                                  const Status& status,
                                  const nlohmann::json& data)
{
    query["server_reply"] = buildServerReplyAsJson(status, data);
    return query.dump();
}

} // end reply namespace