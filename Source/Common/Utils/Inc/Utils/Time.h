/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#pragma once

#include <chrono>
#include <ctime>
#include <stdint.h>
#include <string>

namespace Utils
{

namespace Time
{

namespace stdc = std::chrono;

//-----------------------------------------------------------------------------

typedef stdc::system_clock Clock;

typedef Clock::time_point Point;
typedef Clock::duration   Duration;

typedef stdc::nanoseconds  Nanoseconds;
typedef stdc::microseconds Microseconds;
typedef stdc::milliseconds Milliseconds;
typedef stdc::seconds      Seconds;
typedef stdc::minutes      Minutes;
typedef stdc::hours        Hours;

//-----------------------------------------------------------------------------

extern Point AppStart;

//-----------------------------------------------------------------------------

Point Now();

Duration GetTimeSinceAppStart();

Point GetTimePointFromComponents(
    int32_t day,
    int32_t month,
    int32_t year,
    int32_t hour,
    int32_t minutes,
    int32_t seconds
);

Duration GetDurationFromComponents(
    uint64_t hours = 0,
    uint64_t minutes = 0,
    uint64_t seconds = 0,
    uint64_t milliseconds = 0,
    uint64_t microseconds = 0
);

//-----------------------------------------------------------------------------

std::string GetTimePointString(Point p);
std::string GetHMSString(Point p);

std::string GetDayString(Point p);
std::string GetMonthString(Point p);

int32_t GetDayOfWeek(Point p);
int32_t GetDayOfMonth(Point p);
int32_t GetDayOfYear(Point p);

int32_t GetMonth(Point p);
int32_t GetYear(Point p);

int32_t GetHours(Point p);
int32_t GetMinutes(Point p);
int32_t GetSeconds(Point p);

bool IsDST(Point p);

//-----------------------------------------------------------------------------

std::string GetDayName(int32_t);
std::string GetMonthName(int32_t);

template <typename T>
static T duration_cast(Duration d)
{
    return stdc::duration_cast<T>(d);
}

//-----------------------------------------------------------------------------

} // namespace Time

} // namespace Utils
