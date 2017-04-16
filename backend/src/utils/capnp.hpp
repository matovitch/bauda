#ifndef __CAPNP_UTILS_H__
#define __CAPNP_UTILS_H__

#include <kj/io.h>

#include <algorithm>
#include <string>

namespace capnp_utils
{

std::string stringFromMessage(capnp::MallocMessageBuilder& message)
{
    kj::VectorOutputStream kjVectorOutputStream;

    writePackedMessage(kjVectorOutputStream, message);

    auto kjArray = kjVectorOutputStream.getArray();

    std::string messageAsString;

    messageAsString.resize(kjArray.size());

    std::copy(kjArray.begin(), kjArray.end(), messageAsString.begin());

    return messageAsString;
}

} // end capnp_utils namspace

#endif //__CAPNP_UTILS_H__