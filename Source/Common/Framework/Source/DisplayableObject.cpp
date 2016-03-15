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
    m_position = vec3(0.0f, 0.0f, 0.0f);
    m_scale    = vec3(1.0f, 1.0f, 1.0f);
    m_rotation = vec3(0.0f, 0.0f, 0.0f);
}

//-----------------------------------------------------------------------------

void DisplayableObject::SetPosition(vec3 const& position)
{
    m_position = position;
}

//-----------------------------------------------------------------------------

void DisplayableObject::SetScale(float s)
{
    SetScale(vec3(s, s, s));
}

//-----------------------------------------------------------------------------

void DisplayableObject::SetScale(vec3 const& scale)
{
    m_scale = scale;
}

//-----------------------------------------------------------------------------

void DisplayableObject::SetRotation(vec3 const& rotation)
{
    m_rotation = rotation;
}

//-----------------------------------------------------------------------------

vec3 DisplayableObject::GetPosition()
{
    return m_position;
}

//-----------------------------------------------------------------------------

vec3 DisplayableObject::GetScale()
{
    return m_scale;
}

//-----------------------------------------------------------------------------

vec3 DisplayableObject::GetRotation()
{
    return m_rotation;
}

//-----------------------------------------------------------------------------

} // namespace Framework
