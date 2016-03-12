/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#include "UtilsPch.h"

#include <functional>

#include <Utils/Exception.h>
#include <Utils/Time.h>

namespace Utils
{

namespace Time
{

//-----------------------------------------------------------------------------

Point AppStart = stdc::system_clock::now();

//-----------------------------------------------------------------------------

Point Now()
{
    return stdc::system_clock::now();
}

Duration GetTimeSinceAppStart()
{
    return stdc::duration_cast<Duration>(Now() - AppStart);
}

Point GetTimePointFromComponents(
    int32_t day,
    int32_t month,
    int32_t year,
    int32_t hours,
    int32_t minutes,
    int32_t seconds)
{
    struct std::tm tm;
    tm.tm_sec   = seconds;
    tm.tm_min   = minutes;
    tm.tm_hour  = hours;

    tm.tm_mday  = day;
    tm.tm_mon   = month - 1;
    tm.tm_year  = year - 1900;
    tm.tm_isdst = -1;

    std::time_t tt = std::mktime(&tm);

    if (tt == -1)
    {
        throw Utils::Exception(E_INVALIDARG, "Unable to create a time point with the given arguments", true);
    }

    return stdc::system_clock::from_time_t(tt);
}

Duration GetDurationFromComponents(
    uint64_t hr,
    uint64_t min,
    uint64_t sec,
    uint64_t ms,
    uint64_t us)
{
    return Duration(Hours(hr) + Minutes(min) + Seconds(sec) + Milliseconds(ms) + Microseconds(us));
}

//-----------------------------------------------------------------------------

template <typename TLambda>
auto GetTimePointElementHelper(Point p, TLambda l) -> decltype(l(struct std::tm()))
{
    std::time_t tt(stdc::system_clock::to_time_t(p));
    struct std::tm tm;
    
    auto result = localtime_s(&tm, &tt);

    if (result == EINVAL)
    {
        throw Utils::Exception(E_INVALIDARG, "Invalid argument passed to gmtime_s", true);
    }

    return l(tm);
}

std::string GetTimePointString(Point p)
{
    std::time_t tt(stdc::system_clock::to_time_t(p));

    // ctime_s always writes 26 chars including \n\0
    char buf[26];
    auto result = ctime_s(buf, 26, &tt);

    if (result == EINVAL)
    {
        throw Utils::Exception(E_INVALIDARG, "Invalid argument passed to ctime_s", true);
    }

    return std::string(buf);
}

std::string GetHMSString(Point p)
{
    return GetTimePointElementHelper(p, [](std::tm tm)
    {
        char buf[10];
        sprintf_s(buf, 10, "%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);

        return std::string(buf);
    });
}

std::string GetTimePointDayString(Point p)
{
    return GetTimePointElementHelper(p, [](std::tm tm)
    {
        return GetDayName(tm.tm_wday + 1);
    });
}

std::string GetDayString(Point p)
{
    return GetTimePointElementHelper(p, [](std::tm tm)
    {
        return GetDayName(tm.tm_wday + 1);
    });
}

std::string GetMonthString(Point p)
{
    return GetTimePointElementHelper(p, [](std::tm tm)
    {
        return GetMonthName(tm.tm_mon + 1);
    });
}

int32_t GetDayOfWeek(Point p)
{
    return GetTimePointElementHelper(p, [](std::tm tm)
    {
        return tm.tm_wday;
    });
}

int32_t GetDayOfMonth(Point p)
{
    return GetTimePointElementHelper(p, [](std::tm tm)
    {
        return tm.tm_mday;
    });
}

int32_t GetDayOfYear(Point p)
{
    return GetTimePointElementHelper(p, [](std::tm tm)
    {
        return tm.tm_yday + 1;
    });
}

int32_t GetMonth(Point p)
{
    return GetTimePointElementHelper(p, [](std::tm tm)
    {
        return tm.tm_mon + 1;
    });
}

int32_t GetYear(Point p)
{
    return GetTimePointElementHelper(p, [](std::tm tm)
    {
        return tm.tm_year + 1900;
    });
}

int32_t GetHours(Point p)
{
    return GetTimePointElementHelper(p, [](std::tm tm)
    {
        return tm.tm_hour;
    });
}

int32_t GetMinutes(Point p)
{
    return GetTimePointElementHelper(p, [](std::tm tm)
    {
        return tm.tm_min;
    });
}

int32_t GetSeconds(Point p)
{
    return GetTimePointElementHelper(p, [](std::tm tm)
    {
        return tm.tm_sec;
    });
}

bool IsDST(Point p)
{
    return GetTimePointElementHelper(p, [](std::tm tm)
    {
        return tm.tm_isdst != 0;
    });
}

//-----------------------------------------------------------------------------

std::string GetDayName(int32_t d)
{
    if (d <= 0 || d >= 8)
    {
        throw Utils::Exception(E_INVALIDARG, "Day not normalised, can only get the name of a day in the range 1..7", true);
    }

    switch (d)
    {
    case 1:
        return "Monday";
    case 2:
        return "Tuesday";
    case 3:
        return "Wednesday";
    case 4:
        return "Thursday";
    case 5:
        return "Friday";
    case 6:
        return "Saturday";
    case 7:
        return "Sunday";
    default:
        return "Unknown";
    }
}

std::string GetMonthName(int32_t m)
{
    if (m <= 0 || m >= 13)
    {
        throw Utils::Exception(E_INVALIDARG, "Month not normalised, can only get the name of a month in the range 1..12", true);
    }

    switch (m)
    {
    case 1:
        return "January";
    case 2:
        return "February";
    case 3:
        return "March";
    case 4:
        return "April";
    case 5:
        return "May";
    case 6:
        return "June";
    case 7:
        return "July";
    case 8:
        return "August";
    case 9:
        return "September";
    case 10:
        return "October";
    case 11:
        return "November";
    case 12:
        return "December";
    default:
        return "Unknown";
    }
}

//-----------------------------------------------------------------------------

} // namespace Time

} // namespace Utils
