/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#pragma once

#include <Framework/Camera.h>

#include "Aircraft.h"

namespace Application
{

//-----------------------------------------------------------------------------

class TopDownCamera : public Framework::Camera
{
public:
    TopDownCamera(Aircraft::Ptr const& aircraft);
    virtual ~TopDownCamera() {}

    virtual void Look();

    virtual void Update(uint32_t frameTimeDelta);
    virtual void Projection(int32_t width, int32_t height);

public: // Callbacks
    virtual void KeyAction(unsigned char key, bool keyDown, int x, int y) {}
    virtual void SpecialKeyAction(int key, bool keyDown, int x, int y) {}

    virtual void MouseAction(int button, bool mouseDown, int x, int y);
    virtual void MouseMotion(int x, int y) {}

private:
    Aircraft::Ptr m_aircraft;

    double m_scale;

    int32_t m_width;
    int32_t m_height;
};

//-----------------------------------------------------------------------------

} // namespace Application
