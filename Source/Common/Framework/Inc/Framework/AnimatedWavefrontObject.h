/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#pragma once

#include <cstdint>
#include <memory>

#include <Framework/WavefrontObject.h>

namespace Framework
{

//-----------------------------------------------------------------------------

class AnimatedWavefrontObject : public WavefrontObject
{
public:
    typedef std::shared_ptr<AnimatedWavefrontObject> Ptr;

    AnimatedWavefrontObject(std::string const& objFile, TextureManager::Ptr const& textureManager) :
        WavefrontObject(objFile, textureManager)
    {}
    virtual ~AnimatedWavefrontObject() {}

    virtual void Update(uint32_t frameTimeDelta) = 0;
};

//-----------------------------------------------------------------------------

} // namespace Framework
