/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#include "MariposaYosemitePch.h"

#include "Hangar.h"

#include <Framework/Vector.h>

namespace Application
{

//-----------------------------------------------------------------------------

THangar::THangar(vec3 position, float angle, Framework::TextureManager::Ptr const& textureManager) :
    m_animationTime(0),
    m_doorAngle(0.0f),
    m_upKeyPressed(false),
    m_downKeyPressed(false)
{
    m_position = position;
    m_rotation = vec3(0.0f, angle, 0.0f);

    m_textureHandle = textureManager->GetTexture_SOIL(R"(Resources\corrugatedsteel.dds)");

    m_body = std::make_shared<Framework::WavefrontObject>(R"(Resources\t-hangar.obj)");
    m_doorSegment = std::make_shared<Framework::WavefrontObject>(R"(Resources\t-hangar-door-segment.obj)");
}

//-----------------------------------------------------------------------------

void THangar::Draw()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPushMatrix();

    glDisable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, m_textureHandle);

    glTranslatef(m_position.x, m_position.y, m_position.z);
    glRotatef(m_rotation.x, 1.0f, 0.0f, 0.0f);
    glRotatef(m_rotation.y, 0.0f, 1.0f, 0.0f);
    glRotatef(m_rotation.z, 0.0f, 0.0f, 1.0f);

    m_body->Draw();
    glPushMatrix();
        glTranslatef(3.5f, 1.7f, 0.0f);
        glTranslatef(0.0f, 1.7f, 0.0f);
        glRotatef(m_doorAngle, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.0f, -1.7f, 0.0f);
        m_doorSegment->Draw();

        glPushMatrix();
            glTranslatef(0.0f, -1.7f, 0.0f);
            glTranslatef(0.0f, 1.7f, 0.0f);
            glRotatef(-(m_doorAngle * 2), 0.0f, 0.0f, 1.0f);
            glTranslatef(0.0f, -1.7f, 0.0f);
            m_doorSegment->Draw();
        glPopMatrix();
    glPopMatrix();

    glPopMatrix();
    glPopAttrib();
}

//-----------------------------------------------------------------------------

void THangar::Update(uint32_t frameTimeDelta)
{
    float angleDelta = 8.0f * (frameTimeDelta / 1000.0f);

    if (m_upKeyPressed)
    {
        m_doorAngle += angleDelta;
    }
    else if (m_downKeyPressed)
    {
        m_doorAngle -= angleDelta;
    }

    if (m_doorAngle < 0.0f)
    {
        m_doorAngle = 0.0f;
    }
    else if (m_doorAngle > 88.0f)
    {
        m_doorAngle = 88.0f;
    }
}

//-----------------------------------------------------------------------------

void THangar::SpecialKeyAction(int key, bool keyDown, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        m_upKeyPressed = keyDown;
        break;
    case GLUT_KEY_DOWN:
        m_downKeyPressed = keyDown;
        break;
    }
}

//-----------------------------------------------------------------------------

} // namespace Application
