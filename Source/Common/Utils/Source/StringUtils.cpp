/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#pragma once

#include "UtilsPch.h"

#include <Utils/Assert.h>
#include <Utils/StringUtils.h>

#include <algorithm>
#include <string>
#include <regex>
#include <Windows.h>

namespace Utils
{

std::wstring StringToWString(
    std::string const& s)
{
    return StringToWString(s.data(), s.size());
}

std::wstring StringToWString(
    char const* s,
    size_t size)
{
    if (size == 0)
    {
        return std::wstring();
    }

    int length = MultiByteToWideChar(
        CP_UTF8,
        0,
        s,
        static_cast<int>(size),
        nullptr,
        0
    );

    std::wstring result;
    if (length > 0)
    {
        result.resize(length);
        MultiByteToWideChar(
            CP_UTF8,
            0,
            s,
            static_cast<int>(size),
            &result[0],
            length
        );
    }
    else
    {
        Assert(false);
    }
    return result;
}

std::string WStringToString(
    std::wstring const& w)
{
    return WStringToString(w.data(), w.length());
}

std::string WStringToString(
    wchar_t const* w,
    size_t size)
{
    if (size == 0)
    {
        return std::string();
    }

    int length = WideCharToMultiByte(
        CP_UTF8,
        0,
        w,
        static_cast<int>(size),
        nullptr,
        0,
        nullptr,
        nullptr);

    std::string result;
    if (length > 0)
    {
        result.resize(length);
        WideCharToMultiByte(
            CP_UTF8,
            0,
            w,
            static_cast<int>(size),
            &result[0],
            length,
            nullptr,
            nullptr);
    }
    else
    {
        Assert(false);
    }
    return result;
}

std::vector<Utils::IO::byte> StringToByteVector(
    std::string const& s)
{
    return std::vector<Utils::IO::byte>(s.begin(), s.end());
}

std::string ByteVectorToString(
    std::vector<Utils::IO::byte> const& v)
{
    return std::string(v.begin(), v.end());
}

std::vector<std::string> SplitRegex(
    std::string const& s,
    std::string const& r)
{
    std::vector<std::string> result;

    std::regex regex(r);
    for (std::sregex_token_iterator i(s.begin(), s.end(), regex, -1), endI; i != endI; ++i)
    {
        result.push_back(*i);
    }
    return result;
}

std::vector<std::wstring> SplitRegex(
    std::wstring const& w,
    std::wstring const& r)
{
    std::vector<std::wstring> result;
    
    std::wregex regex(r);
    for (std::wsregex_token_iterator i(w.begin(), w.end(), regex, -1), endI; i != endI; ++i)
    {
        result.push_back(*i);
    }
    return result;
}

} // namespace Utils
