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

class OrbitCamera : public Framework::Camera
{
public:
    OrbitCamera(Aircraft::Ptr const& aircraft);
    virtual ~OrbitCamera() {}

    virtual void Look();
    virtual void Update(uint32_t frameTimeDelta) {}

public: // Callbacks
    virtual void MouseAction(int button, bool mouseDown, int x, int y);
    virtual void MouseMotion(int x, int y);

private:
    Aircraft::Ptr m_aircraft;

    double m_theta;
    double m_phi;

    double m_radius;
};

//-----------------------------------------------------------------------------

} // namespace Application
