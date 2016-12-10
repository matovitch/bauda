#ifndef __UWS_UTILS_H__
#define __UWS_UTILS_H__

#include <random>

#include <uWS/uWS.h>

namespace uWS_utils
{
    struct TheadedHub
    {
        std::unique_ptr<std::thread> thread;
        std::unique_ptr<uWS::Hub>    hub;
    };

    typedef std::vector<TheadedHub> TheadedHubs;

    auto pickDefaultGroup(TheadedHubs& threadedHubs)
    {
    	static auto randomEngine = std::default_random_engine(std::random_device{}());
	           auto distribution = std::uniform_int_distribution<uint64_t>(0, threadedHubs.size() - 1);

        return &(threadedHubs[distribution(randomEngine)].hub->getDefaultGroup<uWS::SERVER>());
    }

} // end uWS_utils namespace

#endif // end __UWS_UTILS_H__