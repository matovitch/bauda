#ifndef __STATUS_H__
#define __STATUS_H__

#include <unordered_map>
#include <cstddef>

class Status
{

public:

    enum
    {
        OK,
        KO_NOT_YET_IMPLEMENTED,
        KO_NO_MODEL,
        KO_NO_USERNAME,
        KO_NO_SERVER_QUERY,
        KO_UNKNOWN_SERVER_QUERY
    };

    Status(uint32_t code);

    const std::string& getDescription() const;

    uint32_t getCode() const;

private:

    static const std::unordered_map<uint32_t, const std::string> _DESCRIPTIONS;

    uint32_t _code;
};

#endif // end __STATUS_H__