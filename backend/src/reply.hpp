#ifndef __REPLY_H__
#define __REPLY_H__

#include <string>

#include <nlohmann/json.hpp>

#include "json_utils.hpp"
#include "status.hpp"

namespace reply
{

    static const auto EMPTY_SERVER_REPLY = 
    nlohmann::json
    {
        {"status_code", Status::OK},
        {"status_description", ""},
        {"data", {}}
    };

    const std::string asString(nlohmann::json& query);

    const nlohmann::json serverReply(const std::string& serverQuery, const nlohmann::json& model);

    const nlohmann::json buildLoginReply(const nlohmann::json& model);
    const nlohmann::json buildSigninReply(const nlohmann::json& model);

    nlohmann::json buildServerReplyAsJson(const Status& status,
                                          const nlohmann::json& data = json_utils::EMPTY_JSON);

    const std::string buildFromJson(nlohmann::json& query,
                                    const nlohmann::json& serverReply);

    const std::string buildFromStatus(nlohmann::json& query,
                                      const Status& status,
                                      const nlohmann::json& data = json_utils::EMPTY_JSON);

} // end reply namespace

#endif    // end __REPLY_H__