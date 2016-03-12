/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#pragma once

#include <exception>
#include <string>

#include <Utils/Assert.h>
#include <Utils/Trace.h>

DECLARE_TRACE_AREA(Exception);

#ifndef _WINERROR_
#define S_OK           0x00000000
#define E_ABORT        0x80004004
#define E_ACCESSDENIED 0x80070005
#define E_FAIL         0x80004005
#define E_HANDLE       0x80070006
#define E_INVALIDARG   0x80070057
#define E_NOINTERFACE  0x80004002
#define E_NOTIMPL      0x80004001
#define E_OUTOFMEMORY  0x8007000E
#define E_POINTER      0x80004003
#define E_UNEXPECTED   0x8000FFFF
#endif // !_WINERROR_

namespace Utils
{

struct Exception : public std::exception
{
    Exception(std::string const& message, bool assert = false) :
        m_message(message),
        m_assert(assert),
        m_result(S_OK)
    {
        if (assert)
        {
            TRACE_WARN(Exception, "Throwing Exception with message '%s'", message.c_str());
#ifndef ENV_UNIT_TEST
            Assert(false);
#endif // ENV_UNIT_TEST
        }
        else
        {
            TRACE_IMPORTANT(Exception, "Throwing Exception with message '%s'", message.c_str());
        }
    }

    Exception(long result, std::string const& message, bool assert = false) :
        m_result(result),
        m_message(message),
        m_assert(assert)
    {
        if (assert)
        {
            TRACE_WARN(Exception, "Throwing Exception with message '%s' and HRESULT '0x%.8x'", message.c_str(), result);
#ifndef ENV_UNIT_TEST
            Assert(false);
#endif // ENV_UNIT_TEST
        }
        else
        {
            TRACE_IMPORTANT(Exception, "Throwing Exception with message '%s' and HRESULT '0x%.8x'", message.c_str(), result);
        }
    }

    std::string m_message;
    long m_result;
    bool m_assert;
};

//-----------------------------------------------------------------------------

inline void ThrowIfFailed(long hr)
{
    if (hr < 0)
    {
        throw Exception(hr, "Failed", false);
    }
}

//-----------------------------------------------------------------------------

} // namespace Utils
