#ifndef __CMD_ABSTRACT_H__
#define __CMD_ABSTRACT_H__

#include <cstddef>

#include "common/logger.hpp"

class CmdAbstract : public Loggable
{

public:

    CmdAbstract(const std::string& username);

    void init();

    virtual const std::string name() const = 0;

    const std::string& getUsername();

    const uint64_t getUserid();

private:

    const std::string _username;
    const uint64_t    _userid;
};

#endif // end __CMD_ABSTRACT_H__