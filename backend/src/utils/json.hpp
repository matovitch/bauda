#ifndef __JSON_UTILS_H__
#define __JSON_UTILS_H__

#include <boost/optional.hpp>
#include <nlohmann/json.hpp>

#include <string>

namespace json_utils
{
    static const auto EMPTY_JSON  = nlohmann::json{};

    const auto asNull    = [](const nlohmann::json& json) { return json.is_null   (); };
    const auto asBoolean = [](const nlohmann::json& json) { return json.is_boolean(); };
    const auto asNumber  = [](const nlohmann::json& json) { return json.is_number (); };
    const auto asObject  = [](const nlohmann::json& json) { return json.is_object (); };
    const auto asArray   = [](const nlohmann::json& json) { return json.is_array  (); };
    const auto asString  = [](const nlohmann::json& json) { return json.is_string (); };

    template <typename KindPredicate>
    const boost::optional<const nlohmann::json> getFrom(const nlohmann::json& json, 
                                                        const std::string& key, 
                                                        KindPredicate kindPredicate)
    {
        return (json.find(key) != json.end() && kindPredicate(json[key])) 
            ? boost::optional<const nlohmann::json>{json[key]}
            : boost::optional<const nlohmann::json>{};
    }

} // end json_utils namespace

#endif // end JSON_UTILS_H__
