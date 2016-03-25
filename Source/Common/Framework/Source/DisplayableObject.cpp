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

GLuint DisplayableObject::s_lastID = 0;

//-----------------------------------------------------------------------------

DisplayableObject::DisplayableObject() :
    m_id(++s_lastID)
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

GLuint DisplayableObject::GetID() const
{
    return m_id;
}

//-----------------------------------------------------------------------------

vec3 DisplayableObject::GetPosition() const
{
    return m_position;
}

//-----------------------------------------------------------------------------

vec3 DisplayableObject::GetScale() const
{
    return m_scale;
}

//-----------------------------------------------------------------------------

vec3 DisplayableObject::GetRotation() const
{
    return m_rotation;
}

//-----------------------------------------------------------------------------

} // namespace Framework
