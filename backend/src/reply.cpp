#include "reply.hpp"

namespace reply
{

const std::string asString(nlohmann::json& query)
{
    auto mainLogger = logger::get(Config::get()["log"]["main_logger"]);

    if (!json_utils::exist(query, "model", json_utils::Kind::IS_OBJECT))
    {
        LOG_WARN(mainLogger,
                 "No model found in query. Replying an error.");
        return json_utils::buildReplyAsString(query,
                                              Status(Status::KO_NO_MODEL));
    }

    if (!json_utils::exist(query, "server_query", json_utils::Kind::IS_STRING))
    {
        LOG_WARN(mainLogger,
                 "No server_query found in query. Replying an error.");
        return json_utils::buildReplyAsString(query,
                                              Status(Status::KO_NO_SERVER_QUERY));
    }

    return json_utils::buildReplyAsString
           (
               query,
               serverReply(query["server_query"], query["model"])
           );
}

const nlohmann::json serverReply(const std::string& serverQuery, const nlohmann::json& model)
{
    if (!json_utils::exist(model, "username", json_utils::Kind::IS_STRING))
    {
        LOG_WARN(logger::get(Config::get()["log"]["main_logger"]),
                 "No username found in model. Replying an error.");
        return json_utils::buildServerReply(Status::KO_NO_USERNAME);
    }

    auto userId     = std::hash<std::string>{}(model["username"]);
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

    return json_utils::buildServerReply(Status::KO_UNKNOWN_SERVER_QUERY);
}

const nlohmann::json buildLoginReply(const nlohmann::json& model)
{
    return json_utils::buildServerReply(Status::KO_NOT_YET_IMPLEMENTED);
}

const nlohmann::json buildSigninReply(const nlohmann::json& model)
{
    return json_utils::buildServerReply(Status::KO_NOT_YET_IMPLEMENTED);
}

} // end reply namespace