#ifndef __SCRYPT_UTILS_H__
#define __SCRYPT_UTILS_H__

#include <libscrypt.h>
#include <exception>
#include <cstddef>
#include <random>
#include <string>
#include <array>


namespace scrypt_utils
{

static constexpr std::size_t K_HASH_SIZE = 16;

static const uint64_t K_SCRYPT_N = 16384;
static const uint64_t K_SCRYPT_R =     8;
static const uint64_t K_SCRYPT_P =     1;

typedef std::array<uint8_t, K_HASH_SIZE> Hash;

typedef uint64_t Salt;

struct SaltAndHash
{
    Salt salt;
    Hash hash;
};

Hash hash(const std::string& toHash, const Salt& salt)
{
    Hash hash;

    int hashing = libscrypt_scrypt(reinterpret_cast<const uint8_t*>(toHash.c_str()), 
                                   toHash.size(),
                                   reinterpret_cast<const uint8_t*>(&salt),
                                   sizeof(uint64_t),
                                   K_SCRYPT_N,
                                   K_SCRYPT_R,
                                   K_SCRYPT_P,
                                   hash.data(),
                                   sizeof(Hash));

    if (hashing < 0)
    {
        throw std::runtime_error("Error while hashing the password.");
    }

    return hash;
}

Salt craftSalt()
{
    static auto randomEngine = std::default_random_engine(std::random_device{}());
           auto distribution = std::uniform_int_distribution<uint64_t>();
    return distribution(randomEngine);
}

SaltAndHash craftSaltAndHash(const std::string& toHashWithSalt)
{
    const Salt& salt = craftSalt();

    return {salt, hash(toHashWithSalt, salt)};
}

} // end scrypt_utils namespace 

#endif // __SCRYPT_UTILS_H__