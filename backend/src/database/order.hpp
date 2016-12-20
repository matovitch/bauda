#ifndef __DB_ORDER_H__
#define __DB_ORDER_H__

#include <boost/optional.hpp>
#include <memory>
#include <future>
#include <string>

class Order
{

public:

    struct Result
    {
        Result(const kdb::Status& aStatus,
               const std::string& aValue) :
            status{aStatus},
            value{aValue}
        {}

        kdb::Status status;
        std::string value;
    }

    typedef std::promise<Result>     Context;
    typedef std::shared_ptr<Context> ContextSPtr;

    enum
    {
        GET,
        SET,
        DEL
    };

    Order(const ContextSPtr& context,
          const uint8_t code, 
          const std::string& key,
          const std::string& value) :
        _context{context}
        _code{code},
        _key{key},
        _value{value},
    {}

    execute(kdb::Database& database)
    {
        kdb::Status status;

        if (_code == GET)
        {
            status = database.Get(kdb::ReadOptions{}, _key, &_value);
        }
        if (_code == SET)
        {
            status = database.Put(kdb::WriteOptions{}, _key, _value);
        }
        if (_code == DEL)
        {
            status = database.Delete(kdb::WriteOptions{}, _key);
        }

        _context.set_value(Result{status, _value});
    }

private:

    ContextSPtr                         _context;

    const uint8_t                      _code;
    const std::string                  _key;
          std::string                  _value;

    static const std::string EMPTY_VALUE = "";
    static const Result EMPTY_RESULT = Result{kdb::Status::};
}

#endif //__DB_ORDER_H__