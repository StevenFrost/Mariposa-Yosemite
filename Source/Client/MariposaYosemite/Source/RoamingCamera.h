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

class RoamingCamera : public Framework::Camera
{
public:
    RoamingCamera() {}
    virtual ~RoamingCamera() {}

    virtual void Look();
};

//-----------------------------------------------------------------------------

} // namespace Application
