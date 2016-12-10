#ifndef __JSON_UTILS_H__
#define __JSON_UTILS_H__

#include <nlohmann/json.hpp>
#include <string>

#include "status.hpp"

namespace json_utils
{
    static const auto EMPTY_JSON  = nlohmann::json{};
    static const auto EMPTY_SERVER_REPLY = 
        nlohmann::json
        {
            {"status_code", Status::OK},
            {"status_description", ""},
            {"data", {}}
        };

    enum Kind
    {
        IS_NULL,
        IS_BOOLEAN,
        IS_NUMBER,
        IS_OBJECT,
        IS_ARRAY,
        IS_STRING
    };

    bool exist(const nlohmann::json& json, const std::string& key, Kind kind);

    nlohmann::json buildServerReply(const Status& status,
                                    const nlohmann::json& data = EMPTY_JSON);

    const std::string buildReplyAsString(nlohmann::json& query,
                                         const nlohmann::json& serverReply);

    const std::string buildReplyAsString(nlohmann::json& query,
                                         const Status& status,
                                         const nlohmann::json& data = EMPTY_JSON);

} // end json_utils namespace

#endif // end JSON_UTILS_H__
