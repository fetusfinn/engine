/*
 *  util.h
 */
#pragma once

#include <unordered_map>

#include "global.h"


timestamp_t timestamp();


template<class T1, class T2>
T1 get_from_map(std::unordered_map<T2, T1> _map, T2 index)
{
    T1 ret;
    try
    {
        ret = _map.at(index);
    }
    catch(std::exception& e)
    {
        error("Cannot find index in map");
        return ret;
    }
    
    return ret;
}

template<class T1, class T2>
void insert_into_map(std::unordered_map<T2, T1>& _map, T2 index, T1 val)
{
    try
    {
        _map.at(index);
    }
    catch(std::exception& e)
    {
        _map.insert(std::make_pair(index, val));
    }
}

