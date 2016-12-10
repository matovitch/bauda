#include "json_utils.hpp"

#include "status.hpp"

namespace json_utils
{
	bool exist(const nlohmann::json& json, const std::string& key, Kind kind)
	{
		if (json.find(key) == json.end())
		{
			return false;
		}

		if (kind == Kind::IS_NULL)
		{
			return json[key].is_null();
		}
		else
		if (kind == Kind::IS_BOOLEAN)
		{
			return json[key].is_boolean();
		}
		else
		if (kind == Kind::IS_NUMBER)
		{
			return json[key].is_number();
		}
		else
		if (kind == Kind::IS_OBJECT)
		{
			return json[key].is_object();
		}
		else
		if (kind == Kind::IS_ARRAY)
		{
			return json[key].is_array();
		}
		else
		if (kind == Kind::IS_STRING)
		{
			return json[key].is_string();
		}

		return false;
	}

	nlohmann::json buildServerReply(const Status& status,
									const nlohmann::json& data)
	{
		auto server_reply = EMPTY_SERVER_REPLY;

		server_reply["status_code"]        = status.getCode();
		server_reply["status_description"] = status.getDescription();
		server_reply["data"]               = data; 

		return server_reply;
	}

	const std::string buildReplyAsString(nlohmann::json& query,
										 const nlohmann::json& serverReply)
	{
		query["server_reply"] = serverReply;
		return query.dump();
	}

	const std::string buildReplyAsString(nlohmann::json& query,
										 const Status& status,
										 const nlohmann::json& data)
	{
		query["server_reply"] = buildServerReply(status, data);
		return query.dump();
	}

} // end json_utils namespace
