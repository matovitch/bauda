#ifndef __CAPNP_USER_H__
#define __CAPNP_USER_H__

#include "../../capnp/gen/user.capnp.h"
#include <capnp/serialize-packed.h>
#include <capnp/message.h>

#include "utils/scrypt.hpp"
#include "utils/capnp.hpp"

#include <kj/io.h>

#include <string>

namespace user
{

std::string create(const std::string& name,
                   const std::string& password,
                   const std::string& email)
{
    capnp::MallocMessageBuilder message;
    User::Builder user = message.initRoot<User>();

    user.setName (name);
    user.setEmail(email);

    scrypt_utils::HashAndSalt hashAndSalt = scrypt_utils::craftHashAndSalt(password);

    user.getPassword().setHash(capnp::Data::Reader(hashAndSalt.hash.data(), 
                                                   hashAndSalt.hash.size()));
    user.getPassword().setSalt(hashAndSalt.salt);

    return capnp_utils::stringFromMessage(message);
}

} // end user namespace



#endif //__CAPNP_USER_H__