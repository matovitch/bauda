#ifndef __REPLY_H__
#define __REPLY_H__

#include <string>

#include <nlohmann/json.hpp>

#include "common/status.hpp"
#include "common/logger.hpp"
#include "utils/json.hpp"

namespace reply
{
    /**
     * Entry point, build a reply as string
     */
    const std::string asString(nlohmann::json& query);

    /**
     * Create the user logger and dispatch query types
     */
    const nlohmann::json serverReply(const std::string& serverQuery, const nlohmann::json& model);

    /**
     * Process each query type and build a reply
     */

    const nlohmann::json buildLoginReply(const std::string& username, const nlohmann::json& model);
    const nlohmann::json buildSigninReply(const std::string& username, const nlohmann::json& model);

    /**
     * List of small helpers to build a reply
     */

    nlohmann::json buildServerReplyAsJson(const Status& status,
                                          const logger::Logger& logger,
                                          const nlohmann::json& data = json_utils::EMPTY_JSON);

    const std::string buildFromJson(nlohmann::json& query,
                                    const nlohmann::json& serverReply);

    const std::string buildFromStatus(nlohmann::json& query,
                                      const Status& status,
                                      const logger::Logger& logger,
                                      const nlohmann::json& data = json_utils::EMPTY_JSON);

    static const auto EMPTY_SERVER_REPLY = 
    nlohmann::json
    {
        {"status_code", Status::KO},
        {"data", {}}
    };

} // end reply namespace

#endif    // end __REPLY_H__