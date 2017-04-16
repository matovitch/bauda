#include "database/order.hpp"

const Order::Result Order::Result::EMPTY_RESULT = Order::Result{kdb::Status::NotFound("EMPTY_RESULT"), ""};

const std::string Order::EMPTY_VALUE = "";

Order::Order(const std::shared_ptr<Context>& context,
             const uint8_t code, 
             const std::string& key,
             const std::string& value) :
    _context{context},
    _code{code},
    _key{key},
    _value{value}
{}

void Order::execute(kdb::Database& database)
{
    kdb::Status status;
    kdb:: ReadOptions  readOptions;
    kdb::WriteOptions writeOptions;

    if (_code == GET)
    {
        status = database.Get(readOptions, _key, &_value);
    }
    if (_code == SET)
    {
        status = database.Put(writeOptions, _key, _value);
    }
    if (_code == DEL)
    {
        status = database.Delete(writeOptions, _key);
    }

    _context->setResult(status, _value);
}