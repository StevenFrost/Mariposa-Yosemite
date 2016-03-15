/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#pragma once

#include <vector>

#include <Framework/Scene.h>

#include "Environment.h"
#include "GroundPolygon.h"

namespace Application
{

//-----------------------------------------------------------------------------

class AirportScene : public Framework::Scene
{
public:
    typedef std::shared_ptr<AirportScene> Ptr;

    AirportScene(Environment::Ptr const& environment) :
        m_environment(environment)
    {}
    virtual ~AirportScene() {}

    virtual void Initialise();
    virtual void Draw();

public: // Callbacks
    virtual void KeyAction(unsigned char key, bool keyDown, int x, int y);

private:
    Environment::Ptr m_environment;

    std::vector<GroundPolygon::Ptr> m_groundPolygons;
};

//-----------------------------------------------------------------------------

} // Application
