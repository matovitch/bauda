#ifndef __CAPNP_USER_H__
#define __CAPNP_USER_H__

#include <string>

namespace user
{

std::string create(const std::string& name,
                   const std::string& password,
                   const std::string& email);

bool checkPassword(const std::string& userAsString, 
                   const std::string& password);

} // end user namespace



#endif //__CAPNP_USER_H__