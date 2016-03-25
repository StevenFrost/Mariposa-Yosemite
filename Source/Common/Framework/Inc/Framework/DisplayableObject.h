/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#pragma once

#include <memory>

#include <Framework/Vector.h>

namespace Framework
{

//-----------------------------------------------------------------------------

class DisplayableObject
{
public:
    typedef std::shared_ptr<DisplayableObject> Ptr;

    DisplayableObject();
    virtual ~DisplayableObject() {}

    virtual void Draw() = 0;
    virtual void Update(uint32_t frameTimeDelta) {}

    void SetPosition(vec3 const& position);
    void SetScale(float s);
    void SetScale(vec3 const& scale);
    void SetRotation(vec3 const& rotation);

    vec3 GetPosition();
    vec3 GetScale();
    vec3 GetRotation();

protected:
    vec3 m_position;
    vec3 m_scale;
    vec3 m_rotation;
};

//-----------------------------------------------------------------------------

} // namespace Framework
