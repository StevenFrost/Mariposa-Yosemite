/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#pragma once

#include <memory>

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

    void SetPosition(float x, float y, float z);
    void SetScale(float s);
    void SetScale(float x, float y, float z);
    void SetRotation(float x, float y, float z);

    float* GetPosition();
    float* GetScale();
    float* GetRotation();

private:
    float m_position[3];
    float m_scale[3];
    float m_rotation[3];
};

//-----------------------------------------------------------------------------

} // namespace Framework
