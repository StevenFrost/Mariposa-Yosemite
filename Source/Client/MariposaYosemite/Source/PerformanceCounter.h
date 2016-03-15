/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#pragma once

#include <cstdint>
#include <memory>
#include <string>

//-----------------------------------------------------------------------------

class PerformanceCounter
{
public:
    typedef std::shared_ptr<PerformanceCounter> Ptr;

    PerformanceCounter() :
        StartTime(0.0),
        Counter(0),
        FramesPerSecond(0)
    {}

    std::string GetFPSString()
    {
        char buf[64];
        sprintf_s(buf, "%d", FramesPerSecond);
        return buf;
    }

    std::string GetMSString()
    {
        char buf[64];
        sprintf_s(buf, "%.2fms", 1000.0 / double(FramesPerSecond));
        return buf;
    }

public:
    double   StartTime;
    uint32_t Counter;
    uint32_t FramesPerSecond;
};

//-----------------------------------------------------------------------------
