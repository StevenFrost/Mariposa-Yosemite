/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#include "FrameworkPch.h"

#include <Framework/DisplayableObject.h>

namespace Framework
{

//-----------------------------------------------------------------------------

DisplayableObject::DisplayableObject()
{
    m_position[0] = 0.0f;
    m_position[1] = 0.0f;
    m_position[2] = 0.0f;

    m_scale[0] = 1.0f;
    m_scale[1] = 1.0f;
    m_scale[2] = 1.0f;

    m_rotation[0] = 0.0f;
    m_rotation[1] = 0.0f;
    m_rotation[2] = 0.0f;
}

//-----------------------------------------------------------------------------

void DisplayableObject::SetPosition(float x, float y, float z)
{
    m_position[0] = x;
    m_position[1] = y;
    m_position[2] = z;
}

//-----------------------------------------------------------------------------

void DisplayableObject::SetScale(float s)
{
    SetScale(s, s, s);
}

//-----------------------------------------------------------------------------

void DisplayableObject::SetScale(float x, float y, float z)
{
    m_scale[0] = x;
    m_scale[1] = y;
    m_scale[2] = z;
}

//-----------------------------------------------------------------------------

void DisplayableObject::SetRotation(float x, float y, float z)
{
    m_rotation[0] = x;
    m_rotation[1] = y;
    m_rotation[2] = z;
}

//-----------------------------------------------------------------------------

float *DisplayableObject::GetPosition()
{
    return m_position;
}

//-----------------------------------------------------------------------------

float *DisplayableObject::GetScale()
{
    return m_scale;
}

//-----------------------------------------------------------------------------

float *DisplayableObject::GetRotation()
{
    return m_rotation;
}

//-----------------------------------------------------------------------------

} // namespace Framework
