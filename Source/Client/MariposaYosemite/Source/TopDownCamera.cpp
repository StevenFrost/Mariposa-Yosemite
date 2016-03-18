/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#include "MariposaYosemitePch.h"

#include "TopDownCamera.h"

namespace Application
{

//-----------------------------------------------------------------------------

TopDownCamera::TopDownCamera(Aircraft::Ptr const& aircraft) :
    m_aircraft(aircraft),
    m_scale(2.0)
{
    m_eyePosition = vec3(0.0f, 1000.0f, 0.0f);
    m_viewDirection = vec3(0.0f, -1.0f, 0.0f);
    m_up = vec3(0.0f, 0.0f, -1.0f);
}

//-----------------------------------------------------------------------------

void TopDownCamera::Look()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        m_eyePosition.x, m_eyePosition.y, m_eyePosition.z,
        m_eyePosition.x + m_viewDirection.x, m_eyePosition.y + m_viewDirection.y, m_eyePosition.z + m_viewDirection.z,
        m_up.x, m_up.y, m_up.z
    );
}

//-----------------------------------------------------------------------------

void TopDownCamera::Update(uint32_t frameTimeDelta)
{
    vec3 aircraftPosition = m_aircraft->GetPosition();
    m_eyePosition = vec3(aircraftPosition.x, m_eyePosition.y, aircraftPosition.z);
}

//-----------------------------------------------------------------------------

void TopDownCamera::Projection(int32_t width, int32_t height)
{
    glOrtho(-width * m_scale, width * m_scale, -height * m_scale, height * m_scale, 1.0, 5000.0);
}

//-----------------------------------------------------------------------------

void TopDownCamera::MouseAction(int button, bool mouseDown, int x, int y)
{
    if ((button == 3) || (button == 4))
    {
        if (button == 3)
        {
            m_scale += 0.025;
        }
        else if (button == 4 && m_scale > 0.1)
        {
            m_scale -= 0.025;
        }
        OnProjectionChanged();
    }
}

//-----------------------------------------------------------------------------

} // namespace Application
