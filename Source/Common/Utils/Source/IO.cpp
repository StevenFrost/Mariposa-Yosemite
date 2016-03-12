/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#include "UtilsPch.h"

#include <Utils/IO.h>

#include <cstdio>
#include <fstream>
#include <iterator>
#include <sys/stat.h>

#include <Utils/Exception.h>

namespace Utils
{

namespace IO
{

namespace File
{

bool Delete(std::string const& file)
{
    return remove(file.c_str()) == 0;
}

bool Exists(std::string const& file)
{
    struct _stat64 buffer;
    return _stat64(file.c_str(), &buffer) == 0;
}

void Copy(std::string const& sourcePath, std::string const& destPath)
{
    std::ifstream source(sourcePath, std::ios::binary);
    std::ofstream destination(destPath, std::ios::binary);
    destination << source.rdbuf();
    source.close();
    destination.close();
}

std::vector<byte> ReadBytes(std::string const& location, size_t position, size_t length)
{
    std::ifstream file(location, std::ios::binary | std::ios::in);
    if (file.is_open() && !file.fail())
    {
        file.seekg(0, std::ios::end);

        std::ifstream::pos_type pos = position;
        std::ifstream::pos_type len = length;
        std::ifstream::pos_type size = file.tellg();

        if (len == 0ll && pos == 0ll)
        {
            len = size;
        }
        else if (len + pos > size)
        {
            len = size - pos;
        }

        if (pos > size)
        {
            throw Utils::Exception("Unable to read past end of file.", false);
        }

        file.seekg(pos, std::ios::beg);

        auto dataSize = static_cast<std::vector<byte>::size_type>(len);
        auto data = std::vector<byte>(dataSize + 1);
        file.read(data.data(), dataSize);
        file.close();

        data.data()[dataSize] = '\0';

        return data;
    }
    else
    {
        file.close();
        throw Utils::Exception("Unable to open " + location, false);
    }
}

std::vector<byte> ReadAllBytes(std::string const& location)
{
    return ReadBytes(location);
}

std::string ReadText(std::string const& location, size_t position, size_t length)
{
    auto data = ReadBytes(location, position, length);
    return std::string(data.begin(), data.end());
}

std::string ReadAllText(std::string const& location)
{
    return ReadText(location);
}

void WriteBytes(std::string const& location, std::vector<byte> const& data, size_t position, size_t length)
{
    std::ofstream file(location, std::ios::binary | std::ios::out);
    if (file.is_open() && !file.fail())
    {
        if (length == 0)
        {
            length = data.size() * sizeof(byte);
        }

        file.seekp(position, std::ios::beg);
        file.write(data.data(), length);
        file.close();
    }
    else
    {
        file.close();
        throw Utils::Exception("Unable to open " + location, false);
    }
}

void WriteAllBytes(std::string const& location, std::vector<byte> const& data)
{
    WriteBytes(location, data);
}

void WriteText(std::string const& location, std::string const& data, size_t position, size_t length)
{
    WriteBytes(location, std::vector<byte>(data.begin(), data.end()), position, length);
}

void WriteAllText(std::string const& location, std::string const& data)
{
    WriteText(location, data);
}

} // namespace File

} // namespace IO

} // namespace Utils
