/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#pragma once

#include <memory>
#include <string>
#include <vector>

#include <Framework/DisplayableObject.h>
#include <Framework/TextureManager.h>

namespace Framework
{

//-----------------------------------------------------------------------------

class WavefrontObject : public DisplayableObject
{
public:
    WavefrontObject(std::string const& objFile, TextureManager::Ptr const& textureManager);

    virtual void Draw();

private:
    void ReadOBJ();

private:
    TextureManager::Ptr m_textureManager;

    std::string        m_file;
    std::vector<float> m_data; // { vec3 position, vec3 normal, vec2 texCoord }
};

//-----------------------------------------------------------------------------

} // namespace Framework
