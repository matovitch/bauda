#include "interface/reply.hpp"

#include <string>

#include <nlohmann/json.hpp>

#include "command/cmd_name.hpp"
#include "command/signin.hpp"
#include "command/login.hpp"
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
        MY_LOG_WARN(mainLogger, "No model found in query. Replying an error.");
        return buildFromStatus(query, Status::KO_NO_MODEL, mainLogger);
    }

    if (!serverQuery)
    {
        MY_LOG_WARN(mainLogger, "No server_query found in query. Replying an error.");
        return buildFromStatus(query, Status::KO_NO_SERVER_QUERY, mainLogger);
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
    auto mainLogger = logger::get(Config::get()["log"]["main_logger"]);

    auto username = json_utils::getFrom(model, "username", json_utils::asString);

    if (!username)
    {
        MY_LOG_WARN(logger::get(Config::get()["log"]["main_logger"]),
                    "No username found in model. Replying an error.");

        return buildServerReplyAsJson(Status::KO_NO_USERNAME, mainLogger);
    }

    MY_LOG_INFO(mainLogger, "Proccessing server query of type <{}>", serverQuery);

    if (serverQuery == K_CMD_NAME_LOGIN)
    {
        return buildLoginReply(*username, model);
    }
    if (serverQuery == K_CMD_NAME_SIGNIN)
    {
        return buildSigninReply(*username, model);
    }

    return buildServerReplyAsJson(Status::KO_UNKNOWN_SERVER_QUERY, mainLogger);
}

const nlohmann::json buildLoginReply(const std::string& username,
                                     const nlohmann::json& model)
{
    auto mainLogger = logger::get(Config::get()["log"]["main_logger"]);

    auto secret = json_utils::getFrom(model, "secret", json_utils::asObject);

    if (!secret)
    {
        MY_LOG_WARN(mainLogger, "No secret found in model. Replying an error.");
        return buildServerReplyAsJson(Status::KO_NO_SECRET, mainLogger);
    }

    auto password = json_utils::getFrom(*secret, "password", json_utils::asString);

    if (!password)
    {
        MY_LOG_WARN(mainLogger, "No password found in model. Replying an error.");
        return buildServerReplyAsJson(Status::KO_NO_PASSWORD, mainLogger);
    }

    return Login{username}(*password);
}

const nlohmann::json buildSigninReply(const std::string& username,
                                      const nlohmann::json& model)
{
    auto mainLogger = logger::get(Config::get()["log"]["main_logger"]);

    auto secret = json_utils::getFrom(model, "secret", json_utils::asObject);
    auto email  = json_utils::getFrom(model, "email" , json_utils::asString);

    if (!secret)
    {
        MY_LOG_WARN(mainLogger, "No secret found in model. Replying an error.");
        return buildServerReplyAsJson(Status::KO_NO_SECRET, mainLogger);
    }

    if (!email)
    {
        MY_LOG_WARN(mainLogger, "No email found in model. Replying an error.");
        return buildServerReplyAsJson(Status::KO_NO_EMAIL, mainLogger);
    }

    auto password = json_utils::getFrom(*secret, "password", json_utils::asString);

    if (!password)
    {
        MY_LOG_WARN(mainLogger, "No password found in model. Replying an error.");
        return buildServerReplyAsJson(Status::KO_NO_PASSWORD, mainLogger);
    }

    return Signin{username}(*password, *email);
}

nlohmann::json buildServerReplyAsJson(const Status& status,
                                      const logger::Logger& logger,
                                      const nlohmann::json& data)
{
    MY_LOG_DEBUG(logger, "Reply status code {}: {}", status.getCode(), status.getDescription());

    auto server_reply = EMPTY_SERVER_REPLY;

    server_reply["status_code"]        = status.getCode();
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
                                  const logger::Logger& logger,
                                  const nlohmann::json& data)
{
    query["server_reply"] = buildServerReplyAsJson(status,
                                                   logger,
                                                   data);
    return query.dump();
}

} // end reply namespace