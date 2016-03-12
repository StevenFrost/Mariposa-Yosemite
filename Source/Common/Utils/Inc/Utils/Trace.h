/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#pragma once

#include <codecvt>
#include <functional>
#include <map>
#include <memory>
#include <string>

#if FEATURE_TRACE_ENABLED

#define TRACE_IMPORTANT(area, message, ...) g_traceArea##area.Output(Trace::Level::Important, message, __VA_ARGS__)
#define TRACE_ERROR(area, message, ...) g_traceArea##area.Output(Trace::Level::Error, message, __VA_ARGS__)
#define TRACE_WARN(area, message, ...) g_traceArea##area.Output(Trace::Level::Warn, message, __VA_ARGS__)
#define TRACE_INFO(area, message, ...) g_traceArea##area.Output(Trace::Level::Info, message, __VA_ARGS__)
#define TRACE_VERBOSE(area, message, ...) g_traceArea##area.Output(Trace::Level::Verbose, message, __VA_ARGS__)

#define DECLARE_TRACE_AREA(area) extern Trace::Area g_traceArea##area
#define DEFINE_TRACE_AREA(area, level) Trace::Area g_traceArea##area(#area, level)

namespace Trace
{

//-----------------------------------------------------------------------------

enum class Level
{
    Default,
    Error,
    Important,
    Warn,
    Info,
    Verbose
};

//-----------------------------------------------------------------------------

class Area
{
public:
    Area(std::string const& area, Trace::Level level) :
        m_areaName(area), m_level(level)
    {
        if (m_level == Level::Default)
        {
            m_level = Level::Info;
        }
    }

    void Output(Level level, std::string message, ...);

protected:
    void OutputInternal(Level level, std::string const& message, va_list args);

    std::string GetAreaName() { return m_areaName; }
    Trace::Level GetLevel()   { return m_level;    }

private:
    std::string  m_areaName;
    Trace::Level m_level;
};

//-----------------------------------------------------------------------------

extern std::function<void(Level level, std::string const&)> OnTrace;

//-----------------------------------------------------------------------------

} // namespace Trace

#else // FEATURE_TRACE_ENABLED

#define TRACE_IMPORTANT(area, message, ...) 
#define TRACE_ERROR(area, message, ...) 
#define TRACE_WARN(area, message, ...) 
#define TRACE_INFO(area, message, ...) 
#define TRACE_VERBOSE(area, message, ...) 

#define DECLARE_TRACE_AREA(area) 
#define DEFINE_TRACE_AREA(area, level) 

#endif // FEATURE_TRACE_ENABLED
