#include "capnp.hpp"

#include <capnp/serialize-packed.h>
#include <capnp/message.h>

#include <kj/io.h>

#include <algorithm>
#include <memory>
#include <string>

namespace capnp_utils
{

std::string stringFromMessageBuilder(capnp::MallocMessageBuilder& message)
{
    kj::VectorOutputStream kjVectorOutputStream;

    capnp::writePackedMessage(kjVectorOutputStream, message);

    std::string messageAsString;

    messageAsString.resize(kjVectorOutputStream.getArray().size());

    std::copy(kjVectorOutputStream.getArray().begin(), 
              kjVectorOutputStream.getArray().end(), 
              messageAsString.begin());

    return messageAsString;
}

Reader::Reader(const std::string& blobAsString)
{
    _vectorOutputStream.write(blobAsString.data(), blobAsString.size());

    kj::ArrayInputStream arrayInputStream{_vectorOutputStream.getArray()};

    _message = std::make_unique<Message>(arrayInputStream);
}

} // end capnp_utils namspace
