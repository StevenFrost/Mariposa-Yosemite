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

class TextureManager
{
public:
    typedef std::shared_ptr<TextureManager> Ptr;

    TextureManager() {}
    virtual ~TextureManager();

    GLuint GetTexture_BMP(std::string const& fileName, bool linear = true, bool repeat = true, bool generateMips = true);
    GLuint GetTexture_SOIL(std::string const& fileName, bool linear = true, bool repeat = true, bool generateMips = true);

private:
    std::map<std::string, GLuint> m_textures;
};

//-----------------------------------------------------------------------------

} // namespace Framework
