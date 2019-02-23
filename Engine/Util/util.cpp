/*      util.cpp
 *
 *
 *
 */
#include "util.h"

/*
 *  timestamp
 *  Returns the timestamp in miliseconds
 */
timestamp_t timestamp()
{
    using namespace std::chrono;
    auto d = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    return d.count();
}
