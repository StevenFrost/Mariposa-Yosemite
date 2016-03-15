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

    GLuint GetTexture(std::string const& fileName, bool generateMips = true);

private:
    std::map<std::string, GLuint> m_textures;
};

//-----------------------------------------------------------------------------

} // namespace Framework
