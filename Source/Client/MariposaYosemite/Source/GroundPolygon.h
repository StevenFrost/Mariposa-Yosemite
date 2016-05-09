/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#pragma once

#include <memory>
#include <string>

#include <Framework/WavefrontObject.h>

namespace Application
{

//-----------------------------------------------------------------------------

class GroundPolygon : public Framework::WavefrontObject
{
public:
    typedef std::shared_ptr<GroundPolygon> Ptr;

    GroundPolygon(std::string const& objFile, std::string const& textureFile, Framework::TextureManager::Ptr const& textureManager);
    virtual ~GroundPolygon() {}
    
    virtual void Draw();

private:
    GLuint m_textureHandle;
    bool   m_lit;
};

//-----------------------------------------------------------------------------

} // namespace Application
