#ifndef __DB_DATABASE_H__
#define __DB_DATABASE_H__

#include <chrono>
#include <memory>
#include <thread>
#include <string>
#include <unordered_map>

#include <boost/lockfree/queue.hpp>
#include <kingdb/kdb.h>

#include "database/order.hpp"
#include "common/config.hpp"
#include "common/logger.hpp"

static std::unordered_map<std::string, Database*> dbRegister;

class DataBase : public Loggable
{

public:

    DataBase(const std::string& filename)
    {
        Loggable::init("database - " + filename);

        const std::string dbPath = Config::get()["database"]["path"];

        kdb::DatabaseOptions dbOptions;

        dbOptions.compression = Config::get()["database"]["compression"] ? kdb::kLZ4Compression 
                                                                         : kdb::kNoCompression;
        kdb::Database db(dbOptions, dbPath + filename);

        _status = db.Open();

        if (!_status.IsOK())
        {
            auto errorMessage = fmt.format("Could not open database. Status: {}" + _status.ToString());

            LOG_ERROR(logger(), errorMessage);

            throw std::runtime_error(errorMessage);
        }

        dbRegister[filename] = this;

        _thread = std::make_unique<std::thread>(run);
    }
    
    bool pushOrder(const Order& order)
    {
        const uint32_t attemtDelay = Config::get()["database"]["push_delay_in_us"];
        const uint32_t maxAttemts  = Config::get()["database"]["max_push_retry"];
              uint32_t attempt     = 0; 

        while !(_orders.push(order) && attempt < maxRetry)
        {
            std::this_thread::sleep_for(std::chrono::microseconds(push_delay));
            attempt++;
        }
    }

    const boost::optional<const Order::Result&> askAndWait(Order::ContextSPtr& context,
                                                           const uint8_t code, 
                                                           const std::string& key,
                                                           const std::string& value = Order::EMPTY_VALUE)
    {
        if (pushOrder(Order{context, code, key}))
        {
            return boost::optional<const Order::Result&>{context->get_future().get()};
        }

        return boost::optional<const Order::Result&>{};
    }

    bool exist(const std::string key)
    {
        auto context = std::make_shared<Order::Context>();

        auto result = askAndWait(context, Order::GET, key);

        if (result)
        {
            return result->status.IsNotFound();
        }

        return false;
    }

    boost::optional<const std::string&> get(const std::string& key)
    {
        auto context = std::make_shared<Order::Context>();

        auto result = askAndWait(context, Order::GET, key);

        if (result && result->status.IsOK())
        {
            return boost::optional<const std::string&>{result->value};
        }

        return boost::optional<const std::string&>{};
    }

private:

    void run()
    {
        Order order;

        while (true)
        {
            if (!_orders.empty())
            {
                _orders.pop(order);
                order.execute(_database);
            }
        }
    }

    kdb::Database                 _database;
    kdb::Status                   _status;
    boost::lockfree::queue<Order> _orders;
    std::unique_ptr<std::thread>  _thread;
};

#endif // __DB_DATABASE_H__