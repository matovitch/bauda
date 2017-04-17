#include "user.hpp"

#include "../../capnp/gen/user.capnp.h"

#include "utils/scrypt.hpp"
#include "utils/capnp.hpp"

#include <algorithm>
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

    scrypt_utils::SaltAndHash saltAndHash = scrypt_utils::craftSaltAndHash(password);

    user.getPassword().setHash(capnp::Data::Reader(saltAndHash.hash.data(), 
                                                   saltAndHash.hash.size()));
    user.getPassword().setSalt(saltAndHash.salt);

    return capnp_utils::stringFromMessageBuilder(message);
}

bool checkPassword(const std::string& userAsString, 
                   const std::string& password)
{
    capnp_utils::Reader reader{userAsString};

    User::Reader user = reader.get<User>();

    const scrypt_utils::Salt& salt = user.getPassword().getSalt();

    const scrypt_utils::Hash& hash = scrypt_utils::hash(password, salt);

    return std::equal(hash.begin(), hash.end(), user.getPassword().getHash().begin());
}

} // end user namespace
