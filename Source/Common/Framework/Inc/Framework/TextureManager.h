/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#pragma once

#include <map>
#include <memory>
#include <string>

#include <GL/freeglut.h>

namespace Framework
{

//-----------------------------------------------------------------------------

struct TextureLoadOptions
{
    bool Linear;
    bool Repeat;
    bool GenerateMipMaps;
    bool DirectLoadDDS;
};

//-----------------------------------------------------------------------------

class TextureManager
{
public:
    typedef std::shared_ptr<TextureManager> Ptr;

    TextureManager() {}
    virtual ~TextureManager();

    GLuint GetTexture_BMP(std::string const& fileName);
    GLuint GetTexture_BMP(std::string const& fileName, TextureLoadOptions const& options);

    GLuint GetTexture_SOIL(std::string const& fileName);
    GLuint GetTexture_SOIL(std::string const& fileName, TextureLoadOptions const& options);

private:
    std::map<std::string, GLuint> m_textures;
};

//-----------------------------------------------------------------------------

} // namespace Framework
