/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#include "MariposaYosemitePch.h"

#include "OrbitCamera.h"

namespace Application
{

//-----------------------------------------------------------------------------

OrbitCamera::OrbitCamera(Aircraft::Ptr const& aircraft) :
    m_aircraft(aircraft),
    m_theta(-3.75),
    m_phi(-1.24),
    m_radius(12.0)
{}

//-----------------------------------------------------------------------------

void OrbitCamera::Look()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    auto aircraftPosition = m_aircraft->GetPosition();
    m_eyePosition.x = static_cast<float>(aircraftPosition.x + m_radius * cos(m_theta) * sin(m_phi));
    m_eyePosition.z = static_cast<float>(aircraftPosition.z + m_radius * sin(m_phi) * sin(m_theta));
    m_eyePosition.y = static_cast<float>(aircraftPosition.y + m_radius * cos(m_phi));

    gluLookAt(
        m_eyePosition.x, m_eyePosition.y, m_eyePosition.z,
        aircraftPosition.x, aircraftPosition.y, aircraftPosition.z,
        m_up.x, m_up.y, m_up.z
    );
}

//-----------------------------------------------------------------------------

void OrbitCamera::MouseAction(int button, bool mouseDown, int x, int y)
{
    Camera::MouseAction(button, mouseDown, x, y);

    if ((button == 3) || (button == 4))
    {
        if (button == 3)
        {
            m_radius += 1.0;
        }
        else if (button == 4 && m_radius > 1.0)
        {
            m_radius -= 1.0;
        }
    }
}

//-----------------------------------------------------------------------------

void OrbitCamera::MouseMotion(int x, int y)
{
    if (m_mouseDown)
    {
        m_theta += (x - m_mouseX) * 0.01;
        m_phi += (y - m_mouseY) * 0.0035;
    }
    m_mouseX = x;
    m_mouseY = y;
}

//-----------------------------------------------------------------------------

} // namespace Application
