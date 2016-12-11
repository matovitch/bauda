#include "reply.hpp"

#include <string>

#include <nlohmann/json.hpp>

#include "json_utils.hpp"
#include "logger.hpp"

namespace reply
{

const std::string asString(nlohmann::json& query)
{
    auto mainLogger = logger::get(Config::get()["log"]["main_logger"]);

    auto model = json_utils::getFrom(query, "model", json_utils::asObject);

    if (!model)
    {
        LOG_WARN(mainLogger, "No model found in query. Replying an error.");

        return buildFromStatus(query, Status::KO_NO_MODEL);
    }

    auto serverQuery = json_utils::getFrom(query, "server_query", json_utils::asString);

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

    if (serverQuery == "login")
    {
        return buildLoginReply(model);
    }
    if (serverQuery == "signin")
    {
        return buildSigninReply(model);
    }

    return buildServerReplyAsJson(Status::KO_UNKNOWN_SERVER_QUERY);
}

const nlohmann::json buildLoginReply(const nlohmann::json& model)
{
    return buildServerReplyAsJson(Status::KO_NOT_YET_IMPLEMENTED);
}

const nlohmann::json buildSigninReply(const nlohmann::json& model)
{
    return buildServerReplyAsJson(Status::KO_NOT_YET_IMPLEMENTED);
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