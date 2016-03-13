/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#include "FrameworkPch.h"

#include <Framework/Camera.h>

#include <ctype.h>

#include <Framework/VectorMath.h>

namespace Framework
{

//-----------------------------------------------------------------------------

Camera::Camera() :
    m_mouseDown(false),
    m_mouseX(0),
    m_mouseY(0)
{
    Reset();
}

//-----------------------------------------------------------------------------

void Camera::Reset()
{
    m_eyePosition[0] = 0.0f;
    m_eyePosition[1] = 2.0f;
    m_eyePosition[2] = 0.0f;

    m_viewDirection[0] = 0.0f;
    m_viewDirection[1] = 0.0f;
    m_viewDirection[2] = 1.0f;

    m_forward[0] = 0.0f;
    m_forward[1] = 0.0f;
    m_forward[2] = -1.0f;

    m_right[0] = 1.0f;
    m_right[1] = 0.0f;
    m_right[2] = 0.0f;

    m_up[0] = 0.0f;
    m_up[1] = 1.0f;
    m_up[2] = 0.0f;
}

//-----------------------------------------------------------------------------

void Camera::Look()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        m_eyePosition[0], m_eyePosition[1], m_eyePosition[2],
        m_eyePosition[0] + m_viewDirection[0], m_eyePosition[1] + m_viewDirection[1], m_eyePosition[2] + m_viewDirection[2],
        m_up[0], m_up[1], m_up[2]
    );
}

//-----------------------------------------------------------------------------

void Camera::Update(uint32_t frameTimeDelta)
{
    float speed = 0.01f;
    float delta = speed * frameTimeDelta;

    if (m_keys['a'])
    {
        sub(m_eyePosition, m_right, delta);
    }
    if (m_keys['d'])
    {
        add(m_eyePosition, m_right, delta);
    }
    if (m_keys['w'])
    {
        add(m_eyePosition, m_forward, delta);
    }
    if (m_keys['s'])
    {
        sub(m_eyePosition, m_forward, delta);
    }
    Look();
}

//-----------------------------------------------------------------------------

void Camera::GetEyePosition(float &x, float &y, float &z) const
{
    x = m_eyePosition[0];
    y = m_eyePosition[1];
    z = m_eyePosition[2];
}

//-----------------------------------------------------------------------------

void Camera::GetViewDirection(float &x, float &y, float &z) const
{
    x = m_viewDirection[0];
    y = m_viewDirection[1];
    z = m_viewDirection[2];
}

//-----------------------------------------------------------------------------

void Camera::GetForwardVector(float &x, float &y, float &z) const
{
    x = m_forward[0];
    y = m_forward[1];
    z = m_forward[2];
}

//-----------------------------------------------------------------------------

void Camera::GetRightVector(float &x, float &y, float &z) const
{
    x = m_right[0];
    y = m_right[1];
    z = m_right[2];
}

//-----------------------------------------------------------------------------

void Camera::GetUpVector(float &x, float &y, float &z) const
{
    x = m_up[0];
    y = m_up[1];
    z = m_up[2];
}

//-----------------------------------------------------------------------------

void Camera::KeyAction(unsigned char key, bool keyDown, int x, int y)
{
    unsigned char lowerKey = static_cast<unsigned char>(tolower(key));
    m_keys[lowerKey] = keyDown;

    switch (key)
    {
    case ' ':
        Reset();
    default:
        break;
    }
}

//-----------------------------------------------------------------------------

void Camera::SpecialKeyAction(int key, bool keyDown, int x, int y)
{}

//-----------------------------------------------------------------------------

void Camera::MouseAction(int button, bool mouseDown, int x, int y)
{
    m_mouseDown = mouseDown;
    m_mouseX = x;
    m_mouseY = y;
}

//-----------------------------------------------------------------------------

void Camera::MouseMotion(int x, int y)
{
    float sensitivity = 0.01f;
    float dx = static_cast<float>(x - m_mouseX);
    float dy = static_cast<float>(y - m_mouseY);

    if (m_mouseDown)
    {
        if (dx > 0)
        {
            add(m_viewDirection, m_right, dx * sensitivity);
        }
        else
        {
            sub(m_viewDirection, m_right, dx * -sensitivity);
        }

        if (dy > 0)
        {
            sub(m_viewDirection, m_up, dy * sensitivity);
        }
        else
        {
            add(m_viewDirection, m_up, dy * -sensitivity);
        }

        norm(m_viewDirection);
        cross(m_viewDirection, m_up, m_right);
        norm(m_right);

        m_forward[0] = m_viewDirection[0];
        m_forward[2] = m_viewDirection[2];
        norm(m_forward);
    }

    m_mouseX = x;
    m_mouseY = y;
}

//-----------------------------------------------------------------------------

void Camera::PassiveMouseMotion(int x, int y)
{}

//-----------------------------------------------------------------------------

} // namespace Framework
