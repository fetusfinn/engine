/*
 *  math.h
 */
#pragma once

#include <algorithm>
#include "global.h"

namespace math
{
    template <typename T>
    inline T clamp(const T& n, const T& lower, const T& upper)
    {
        return std::max(lower, std::min(n, upper));
    }

    template<typename T>
    inline T make_positive(T n)
    {
        return (n > 0 ? n : -n);
    }
    
    template<typename T>
    inline T make_negative(T n)
    {
        return (n < 0 ? n : -n);
    }
}
