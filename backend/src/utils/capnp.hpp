#ifndef __CAPNP_UTILS_H__
#define __CAPNP_UTILS_H__

#include <capnp/serialize-packed.h>
#include <capnp/message.h>
#include <kj/io.h>

#include <memory>
#include <string>

namespace capnp_utils
{

std::string stringFromMessageBuilder(capnp::MallocMessageBuilder& message);

struct Reader
{
    typedef capnp::PackedMessageReader Message;

    Reader(const std::string& blobAsString);

    template <class T>
    typename T::Reader get()
    {
        return _message->getRoot<T>();
    }

    kj::VectorOutputStream _vectorOutputStream;
    std::unique_ptr<Message> _message;
};

} // end capnp_utils namspace

#endif //__CAPNP_UTILS_H__