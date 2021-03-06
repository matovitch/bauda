#include "common/status.hpp"

#include <unordered_map>

const std::unordered_map<uint32_t, const std::string> Status::_DESCRIPTIONS =
{
    { Status::OK                      , "OK"                     },
    { Status::KO                      , "KO"                     },
    { Status::KO_NO_MODEL             , "Missing model."         },
    { Status::KO_NO_EMAIL             , "Missing email."         },
    { Status::KO_NO_SECRET            , "Missing secret."        },
    { Status::KO_NO_PASSWORD          , "Missing password."      },
    { Status::KO_NO_USERNAME          , "Missing username."      },
    { Status::KO_NO_SERVER_QUERY      , "Missing server_query."  },
    { Status::KO_UNKNOWN_SERVER_QUERY , "Unknown server_query."  },
    { Status::KO_SIGNIN_USERNAME_TAKEN, "Username already taken."},
    { Status::KO_SIGNIN_DATABASE_ERROR, "Database error."        },
    { Status::KO_LOGIN_USER_NOT_FOUND , "User not found."        },
    { Status::KO_LOGIN_WRONG_PASSWORD , "Wrong password."        }
};

Status::Status(uint32_t code) : _code(code) {}

const std::string& Status::getDescription() const
{
    return (_DESCRIPTIONS.find(_code) != _DESCRIPTIONS.end()) ? _DESCRIPTIONS.at(_code)
                                                              : _DESCRIPTIONS.at(Status::KO);
}

uint32_t Status::getCode() const
{
    return _code;
}