#ifndef __CMD_SIGNIN_H__
#define __CMD_SIGNIN_H__

#include "cmd_abstract.hpp"

struct Signin : public CmdAbstract
{
    Signin(const std::string& username);

    const std::string name() const;

    const nlohmann::json operator()(const std::string& password,
                                     const std::string& email);
};

#endif // end __CMD_SIGNIN_H__