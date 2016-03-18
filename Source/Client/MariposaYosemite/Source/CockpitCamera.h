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

class CockpitCamera : public Framework::Camera
{
public:
    CockpitCamera(Aircraft::Ptr const& aircraft);
    virtual ~CockpitCamera() {}

    virtual void Update(uint32_t frameTimeDelta);

public: // Callbacks
    virtual void KeyAction(unsigned char key, bool keyDown, int x, int y) {}
    virtual void SpecialKeyAction(int key, bool keyDown, int x, int y) {}

private:
    Aircraft::Ptr m_aircraft;
};

//-----------------------------------------------------------------------------

} // namespace Application
