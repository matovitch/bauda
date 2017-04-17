#include "database/database.hpp"

#include "database/order.hpp"

#include "common/logger.hpp"
#include "common/config.hpp"

#include <kingdb/kdb.h>

#include <boost/optional.hpp>
#include <unordered_map>
#include <utility>
#include <cstddef>
#include <string>
#include <memory>

DataBase::DataBase(const std::string& name)
{
    Loggable::init("database - " + name);

    readSettings();

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

    MY_LOG_INFO(logger(), "Openning/Creation of database \"{}\" successful.", name);

    _thread = std::make_unique<std::thread>(&DataBase::run, this);
}

bool DataBase::isNotFound(const std::string key)
{
    auto context = askAndWait(Order::GET, key);

    if (!context)
    {
        return false;
    }

    MY_LOG_DEBUG(logger(), "Database traces:\n\tGET \"{}\"\n\t{}", 
                 key, context->getStatus().ToString());

    return context->isNotFound();
}

bool DataBase::set(const std::string& key, const std::string& value)
{
    auto context = askAndWait(Order::SET, key, value);

    if (!context)
    {
        return false;
    }

    MY_LOG_DEBUG(logger(), "Database traces:\n\tSET \"{}\"\n\t{}", 
             key, context->getStatus().ToString());

    return context->isOK();
}

boost::optional<std::string> DataBase::get(const std::string& key)
{
    auto context = askAndWait(Order::GET, key);

    if (!context)
    {
        return boost::optional<std::string>{};
    }

    MY_LOG_DEBUG(logger(), "Database traces:\n\tGET \"{}\"\n\t{}", 
             key, context->getStatus().ToString());

    return context->isOK() ? context->getValue()
                           : boost::optional<std::string>{};
}

void DataBase::readSettings()
{
    const unsigned pushDelayInUs = Config::get()["database"]["push_delay_in_us"];
    const unsigned pollDelayInUs = Config::get()["database"]["poll_delay_in_us"];
    
    _settings.pushDelay      = std::chrono::microseconds{pushDelayInUs};
    _settings.pollDelay      = std::chrono::microseconds{pollDelayInUs};
    _settings.pushMaxAttempt = Config::get()["database"]["push_max_attempt"];
}

bool DataBase::pushOrder(Order* const order)
{
    unsigned attempt = 0; 

    while (!_orders.push(order) && attempt < _settings.pushMaxAttempt)
    {
        std::this_thread::sleep_for(_settings.pushDelay);
        attempt++;
    }

    return attempt != _settings.pushMaxAttempt;
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
        while (_orders.pop(order))
        {
            order->execute(*_database);
        }

        std::this_thread::sleep_for(_settings.pollDelay);
    }
}

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