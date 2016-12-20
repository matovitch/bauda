#ifndef __CMD_LOGIN_H__
#define __CMD_LOGIN_H__

#include "cmd_abstract.hpp"

struct Login : public CmdAbstract
{
    Login(const std::string& username);

    const std::string name() const;

    const nlohmann::json operator()(const std::string& password);
};

#endif // end __CMD_LOGIN_H__