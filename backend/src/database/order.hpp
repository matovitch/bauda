#ifndef __DB_ORDER_H__
#define __DB_ORDER_H__

#include <kingdb/kdb.h>

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

        static const Result EMPTY_RESULT;
    };

    class Context
    {

    public:

        void wait()
        {
            _promise.get_future().get();
        }

        kdb::Status getStatus()
        {
            return _promise.get_future().get().status;
        }

        std::string getValue()
        {
            return _promise.get_future().get().value;
        }

        bool isOK()
        {
            return getStatus().IsOK();
        }

        bool isNotFound()
        {
            return getStatus().IsNotFound();
        }

        void setResult(const Result& result)
        {
            _promise.set_value(result);
        }

    private:

        std::promise<Result> _promise;
    };

    typedef std::shared_ptr<Context> ContextSPtr;

    enum
    {
        GET,
        SET,
        DEL
    };

    Order(const std::shared_ptr<Context>& context,
          const uint8_t code, 
          const std::string& key,
          const std::string& value);
    
    void execute(kdb::Database& database);

    static const std::string EMPTY_VALUE;

private:

    ContextSPtr _context;

    const uint8_t            _code;
    const std::string        _key;
          std::string        _value;
};

#endif //__DB_ORDER_H__