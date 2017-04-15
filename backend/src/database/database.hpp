#ifndef __DB_DATABASE_H__
#define __DB_DATABASE_H__

#include <chrono>
#include <memory>
#include <thread>
#include <string>
#include <unordered_map>

#include <boost/lockfree/queue.hpp>
#include <boost/optional.hpp>
#include <kingdb/kdb.h>

#include "database/order.hpp"
#include "common/config.hpp"
#include "common/logger.hpp"


class DataBase : public Loggable
{

public:

    DataBase(const std::string& name);

    bool isNotFound(const std::string key);

    bool set(const std::string& key, const std::string& value);

    boost::optional<std::string> get(const std::string& key);

private:

    void run();

    bool pushOrder(Order* const order);

    Order::ContextSPtr askAndWait(const uint8_t code, 
                                  const std::string& key,
                                  const std::string& value = Order::EMPTY_VALUE);

    std::unique_ptr<kdb::Database> _database;
    kdb::Status                    _status;
    boost::lockfree::queue<Order*, boost::lockfree::capacity<50>> _orders;
    std::unique_ptr<std::thread>   _thread;
};

namespace database
{
    DataBase& create(const std::string& name);

    DataBase& get(const std::string& name);

} // end database namespace

#endif // __DB_DATABASE_H__