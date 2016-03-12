/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#pragma once

#include <string>
#include <vector>

#include <Utils/IO.h>

namespace Utils
{

std::wstring StringToWString(
    std::string const& s
);

std::wstring StringToWString(
    char const* s,
    size_t size
);

std::string WStringToString(
    std::wstring const& w
);

std::string WStringToString(
    wchar_t const* s,
    size_t size
);

std::vector<Utils::IO::byte> StringToByteVector(
    std::string const& s
);

std::string ByteVectorToString(
    std::vector<Utils::IO::byte> const& v
);

std::vector<std::string> SplitRegex(
    std::string const& s,
    std::string const& r
);

std::vector<std::wstring> SplitRegex(
    std::wstring const& w,
    std::wstring const& r
);

template <class TString>
std::vector<TString> Split(
    TString const& s,
    TString const& d)
{
    TString::size_type startPos = 0;
    TString::size_type endPos = s.find(d, startPos);

    std::vector<TString> result;

    while (endPos != TString::npos)
    {
        result.push_back(s.substr(startPos, endPos - startPos));
        startPos = endPos + d.size();

        endPos = s.find(d, startPos);
    }
    result.push_back(s.substr(startPos, s.size() - startPos));
    return result;
}

template <class TString>
bool RemoveTrailingChar(TString& s, char c)
{
    auto lastCharIdx = s.find_last_of(c);
    auto charExists = lastCharIdx != TString::npos;
    if (!charExists) { return false; }
    while (charExists && lastCharIdx + 1 == s.length())
    {
        s.pop_back();
        lastCharIdx = s.find_last_of(c);
    }
    return true;
}

template <class TString>
bool RemoveLeadingChar(TString& s, char c)
{
    auto firstCharIdx = s.find_first_of(c);
    auto charExists = firstCharIdx != TString::npos;
    if (!charExists) { return false; }
    while (charExists && firstCharIdx == 0)
    {
        s.erase(0, firstCharIdx + 1);
        firstCharIdx = s.find_first_of(c);
    }
    return true;
}

} // namespace Utils
