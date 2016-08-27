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

class THangar : public Framework::UserControlledDisplayableObject
{
public:
    THangar(vec3 position, float angle, Framework::TextureManager::Ptr const& textureManager);
    virtual ~THangar() {}

    virtual void Draw();
    virtual void Update(uint32_t frameTimeDelta);

public: // Callbacks
    virtual void SpecialKeyAction(int key, bool keyDown, int x, int y);

private:
    GLuint m_textureHandle;

    uint32_t m_animationTime;
    float    m_doorAngle;

    bool m_upKeyPressed;
    bool m_downKeyPressed;

    Framework::WavefrontObject::Ptr m_body;
    Framework::WavefrontObject::Ptr m_doorSegment;
};

//-----------------------------------------------------------------------------

} // namespace Application
