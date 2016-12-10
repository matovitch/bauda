#ifndef __REPLY_H__
#define __REPLY_H__

#include <nlohmann/json.hpp>
#include <functional>

#include "json_utils.hpp"
#include "logger.hpp"
#include "config.hpp"

namespace reply
{

const std::string asString(nlohmann::json& query);

const nlohmann::json serverReply(const std::string& serverQuery, const nlohmann::json& model);

const nlohmann::json buildLoginReply(const nlohmann::json& model);
const nlohmann::json buildSigninReply(const nlohmann::json& model);

} // end reply namespace

#endif	// end __REPLY_H__