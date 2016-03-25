/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#pragma once

#include <Framework/TextureManager.h>
#include <Framework/WavefrontObject.h>

namespace Application
{

//-----------------------------------------------------------------------------

class THangar : public Framework::DisplayableObject
{
public:
    THangar(vec3 position, float angle, Framework::TextureManager::Ptr const& textureManager);
    virtual ~THangar() {}

    virtual void Draw();
    virtual void Update(uint32_t frameTimeDelta);

private:
    GLuint m_textureHandle;

    uint32_t m_animationTime;
    float    m_doorAngle;

    Framework::WavefrontObject::Ptr m_body;
    Framework::WavefrontObject::Ptr m_doorSegment;
};

//-----------------------------------------------------------------------------

} // namespace Application
