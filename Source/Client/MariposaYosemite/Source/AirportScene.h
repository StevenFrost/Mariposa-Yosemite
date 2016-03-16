/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#pragma once

#include <vector>

#include <Framework/Scene.h>
#include <Framework/WavefrontObject.h>

#include "Environment.h"

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

    std::vector<Framework::WavefrontObject::Ptr> m_groundPolygons;
};

//-----------------------------------------------------------------------------

} // Application
