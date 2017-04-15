#include "database/database.hpp"

#include "database/order.hpp"

#include "common/logger.hpp"
#include "common/config.hpp"

#include <kingdb/kdb.h>

#include <boost/optional.hpp>
#include <utility>
#include <cstddef>
#include <string>
#include <memory>

namespace database
{
    static std::unordered_map<std::string, std::unique_ptr<DataBase>> REGISTER;

    DataBase& get(const std::string& name)
    {
        return *(REGISTER.find(name)->second);
    }

    DataBase& create(const std::string& name)
    {
        REGISTER.emplace(name, std::make_unique<DataBase>(name));

        return get(name);
    }

} // end database namespace

DataBase::DataBase(const std::string& name)
{
    Loggable::init("database - " + name);

    const std::string dbExtension = Config::get()["database"]["extension"];
    const std::string dbPath      = Config::get()["database"]["path"];
    const std::string rootPath    = Config::get()["root_path"];
    
    _database = std::make_unique<kdb::Database>(kdb::DatabaseOptions{}, 
                                                rootPath + dbPath + name + dbExtension);

    _status = _database->Open();

    if (!_status.IsOK())
    {
        MY_LOG_ERROR(logger(), "Could not open database. Status: {}", _status.ToString());

        throw std::runtime_error("Failed to open a database. Details in the logs...");
    }

    _thread = std::make_unique<std::thread>(&DataBase::run, this);
}

bool DataBase::isNotFound(const std::string key)
{
    auto context = askAndWait(Order::GET, key);

    return context ? context->isNotFound()
                   : false;
}

bool DataBase::set(const std::string& key, const std::string& value)
{
    auto context = askAndWait(Order::SET, key, value);

    return context ? context->isOK()
                   : false;
}

boost::optional<std::string> DataBase::get(const std::string& key)
{
    auto context = askAndWait(Order::GET, key);

    return (context && context->isOK()) ? context->getValue()
                                        : boost::optional<std::string>{};
}


bool DataBase::pushOrder(Order* const order)
{
    const uint32_t attemtDelay = Config::get()["database"]["push_delay_in_us"];
    const uint32_t maxAttemts  = Config::get()["database"]["max_push_retry"];
          uint32_t attempt     = 0; 

    while (!_orders.push(order) && attempt < maxAttemts)
    {
        std::this_thread::sleep_for(std::chrono::microseconds(attemtDelay));
        attempt++;
    }

    return attempt != maxAttemts;
}

Order::ContextSPtr DataBase::askAndWait(const uint8_t code, 
                                        const std::string& key,
                                        const std::string& value)
{
    auto context = std::make_shared<Order::Context>();

    auto order = std::make_unique<Order>(context, code, key, value);

    if (!pushOrder(order.get()))
    {
        MY_LOG_WARN(logger(), "Failed to push an order onto the lockfree queue.");
        return Order::ContextSPtr{};
    }

    context->wait();

    return context;
}


void DataBase::run()
{
    Order* order;

    while (true)
    {
        if (!_orders.empty())
        {
            _orders.pop(order);
            order->execute(*_database);
        }
    }
}