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
        Result() {}

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

        Context() : _result(new Result) {}

        void wait()
        {
            _promise.get_future().get();
        }

        kdb::Status getStatus()
        {
            return _result->status;
        }

        std::string getValue()
        {
            return _result->value;
        }

        bool isOK()
        {
            return getStatus().IsOK();
        }

        bool isNotFound()
        {
            return getStatus().IsNotFound();
        }

        void setResult(const kdb::Status& status, const std::string value)
        {
            _result->status = status;
            _result->value = value;
            _promise.set_value(_result.get());
        }

    private:

        std::unique_ptr<Result> _result;
        std::promise<Result*>  _promise;
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