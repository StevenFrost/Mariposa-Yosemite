/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#pragma once

#include <memory>
#include <string>
#include <vector>

#include <Utils/Exception.h>

namespace Utils
{

namespace IO
{

//-----------------------------------------------------------------------------

typedef char byte;

//-----------------------------------------------------------------------------

struct FileNotFoundException : public Utils::Exception
{
    FileNotFoundException(std::string const& fileName)
        : Utils::Exception("The file '" + fileName + "' could not be found.")
    {}
};

//-----------------------------------------------------------------------------

namespace File
{

bool Delete(std::string const& file);
bool Exists(std::string const& file);
void Copy(std::string const& sourcePath, std::string const& destPath);

std::vector<byte> ReadBytes(std::string const& location, size_t position = 0, size_t length = 0);
std::vector<byte> ReadAllBytes(std::string const& location);
std::string ReadText(std::string const& location, size_t position = 0, size_t length = 0);
std::string ReadAllText(std::string const& location);

void WriteBytes(std::string const& location, std::vector<byte> const& data, size_t position = 0, size_t length = 0);
void WriteAllBytes(std::string const& location, std::vector<byte> const& data);
void WriteText(std::string const& location, std::string const& data, size_t position = 0, size_t length = 0);
void WriteAllText(std::string const& location, std::string const& data);

} // namespace File

//-----------------------------------------------------------------------------

} // namespace IO

} // namespace Utils