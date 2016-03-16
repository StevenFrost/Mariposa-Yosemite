/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#pragma once

#include <map>
#include <vector>

#include <Framework/Camera.h>
#include <Framework/Scene.h>
#include <Framework/WavefrontObject.h>

#include "Environment.h"

namespace Application
{

//-----------------------------------------------------------------------------

enum class CameraType
{
    Roaming,
    Orbit,
    Cockpit
};

//-----------------------------------------------------------------------------

class AirportScene : public Framework::Scene
{
public:
    typedef std::shared_ptr<AirportScene> Ptr;

    AirportScene(Environment::Ptr const& environment);
    virtual ~AirportScene() {}

    virtual void Initialise();
    virtual void Draw();

public: // Callbacks
    virtual void KeyAction(unsigned char key, bool keyDown, int x, int y);

private:
    Environment::Ptr m_environment;

    std::vector<Framework::WavefrontObject::Ptr> m_groundPolygons;
    std::map<CameraType, Framework::Camera::Ptr> m_cameras;
};

//-----------------------------------------------------------------------------

} // Application
