/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#include "UtilsPch.h"

#include <Utils/Trace.h>

#include <cstdarg>
#include <cstdio>
#include <Windows.h>

#include <Utils/StringUtils.h>
#include <Utils/Time.h>

DEFINE_TRACE_AREA(Trace, Trace::Level::Default);

#if FEATURE_TRACE_ENABLED

namespace
{

namespace UT = Utils::Time;

//-----------------------------------------------------------------------------

std::string GetTimeString()
{
    auto d  = UT::GetTimeSinceAppStart();
    auto h  = UT::duration_cast<UT::Hours>(d).count();
    auto m  = UT::duration_cast<UT::Minutes>(d).count();
    auto s  = UT::duration_cast<UT::Seconds>(d).count();
    auto ms = UT::duration_cast<UT::Milliseconds>(d).count();
    
    char time[16];
    sprintf_s(time, "%02d:%02d:%02lld.%03lld",
        h,
        m - (h * 60),
        s - (m * 60),
        ms - (s * 1000)
    );
    return time;
}

//-----------------------------------------------------------------------------

std::string GetLevelString(Trace::Level level)
{
    switch (level)
    {
    case Trace::Level::Error:
        return "Error";
    case Trace::Level::Important:
        return "Important";
    case Trace::Level::Warn:
        return "Warn";
    case Trace::Level::Info:
        return "Info";
    case Trace::Level::Verbose:
        return "Verbose";
    default:
        return "Unknown";
    };
}

//-----------------------------------------------------------------------------

} // namespace

//-----------------------------------------------------------------------------

namespace Trace
{

//-----------------------------------------------------------------------------

std::function<void(Level level, std::string const&)> OnTrace = nullptr;

//-----------------------------------------------------------------------------

void Area::Output(Level level, std::string message, ...)
{
    auto requestedLevel = static_cast<unsigned int>(level);
    auto areaLevel  = static_cast<unsigned int>(m_level);
    if (requestedLevel > areaLevel)
    {
        return;
    }

    va_list varArgs;

    va_start(varArgs, message);
    OutputInternal(level, message, varArgs);
    va_end(varArgs);
}

//-----------------------------------------------------------------------------

void Area::OutputInternal(Level level, std::string const& message, va_list args)
{
    static const size_t BUF_SIZE = 1024;

    char formattedBuffer[BUF_SIZE];
    char wholeLine[BUF_SIZE + 32];

    // Apply the var args to the message string
    _vsnprintf_s(formattedBuffer, BUF_SIZE, _TRUNCATE, message.c_str(), args);

    auto traceTime  = GetTimeString();
    auto traceLevel = GetLevelString(level);
    auto areaName   = GetAreaName();
    
    // Form the final output line. Example: [00:00:00:00][WARN][0x00000000][Trace] Warning!
    sprintf_s(wholeLine, "[%s][%s][0x%08x][%s] %s\n",
        traceTime.c_str(),
        traceLevel.c_str(),
        static_cast<unsigned int>(GetCurrentThreadId()),
        areaName.c_str(),
        formattedBuffer);

    auto out = Utils::StringToWString(wholeLine);
    OutputDebugString(out.c_str());

    if (OnTrace != nullptr)
    {
        OnTrace(level, wholeLine);
    }
}

//-----------------------------------------------------------------------------

} // namespace Trace

#endif // FEATURE_TRACE_ENABLED
