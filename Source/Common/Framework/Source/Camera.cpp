/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#include "FrameworkPch.h"

#include <Framework/Camera.h>

#include <ctype.h>

namespace Framework
{

//-----------------------------------------------------------------------------

Camera::Camera() :
    m_mouseDown(false),
    m_shiftDown(false),
    m_mouseX(0),
    m_mouseY(0)
{
    Reset();
}

//-----------------------------------------------------------------------------

void Camera::Reset()
{
    m_eyePosition   = vec3(0.0f, 2.0f, 0.0f);
    m_viewDirection = vec3(0.0f, 0.0f, 1.0f);
    m_forward       = vec3(0.0f, 0.0f, -1.0f);
    m_right         = vec3(1.0f, 0.0f, 0.0f);
    m_up            = vec3(0.0f, 1.0f, 0.0f);
}

//-----------------------------------------------------------------------------

void Camera::Look()
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

void Camera::Update(uint32_t frameTimeDelta)
{
    float speed = 60.0f * (m_shiftDown ? 2.0f : 1.0f);
    float delta = speed * (frameTimeDelta / 1000.0f);

    if (m_keys['a'])
    {
        m_eyePosition = m_eyePosition - (m_right * delta);
    }
    if (m_keys['d'])
    {
        m_eyePosition = m_eyePosition + (m_right * delta);
    }
    if (m_keys['w'])
    {
        m_eyePosition = m_eyePosition + (m_forward * delta);
    }
    if (m_keys['s'])
    {
        m_eyePosition = m_eyePosition - (m_forward * delta);
    }
    Look();
}

//-----------------------------------------------------------------------------

vec3 Camera::GetEyePosition() const
{
    return m_eyePosition;
}

//-----------------------------------------------------------------------------

vec3 Camera::GetViewDirection() const
{
    return m_viewDirection;
}

//-----------------------------------------------------------------------------

vec3 Camera::GetForwardVector() const
{
    return m_forward;
}

//-----------------------------------------------------------------------------

vec3 Camera::GetRightVector() const
{
    return m_right;
}

//-----------------------------------------------------------------------------

vec3 Camera::GetUpVector() const
{
    return m_up;
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
{
    switch (key)
    {
    case GLUT_KEY_SHIFT_L:
        m_shiftDown = keyDown;
        break;
    }
}

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
    float sensitivity = 0.005f;
    float dx = static_cast<float>(x - m_mouseX);
    float dy = static_cast<float>(y - m_mouseY);

    if (m_mouseDown)
    {
        if (dx > 0)
        {
            m_viewDirection = m_viewDirection + (m_right * (dx * sensitivity));
        }
        else
        {
            m_viewDirection = m_viewDirection - (m_right * (dx * -sensitivity));
        }

        if (dy > 0)
        {
            m_viewDirection = m_viewDirection - (m_up * (dy * sensitivity));
        }
        else
        {
            m_viewDirection = m_viewDirection + (m_up * (dy * -sensitivity));
        }

        m_viewDirection.Normalize();
        m_right = m_viewDirection.Cross(m_up);
        m_right.Normalize();

        m_forward = m_viewDirection;
        m_forward.Normalize();
    }

    m_mouseX = x;
    m_mouseY = y;
}

//-----------------------------------------------------------------------------

void Camera::PassiveMouseMotion(int x, int y) {}

//-----------------------------------------------------------------------------

} // namespace Framework
