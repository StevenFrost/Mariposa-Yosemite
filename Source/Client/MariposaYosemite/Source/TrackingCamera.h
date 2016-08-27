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

class TrackingCamera : public Framework::Camera
{
public:
    TrackingCamera(Aircraft::Ptr const& aircraft);
    virtual ~TrackingCamera() {}

    virtual void Look();

private:
    Aircraft::Ptr m_aircraft;
};

//-----------------------------------------------------------------------------

} // namespace Application
