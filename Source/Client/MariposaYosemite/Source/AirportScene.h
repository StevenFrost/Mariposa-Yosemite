/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#pragma once

#include <Framework/Scene.h>

namespace Application
{

//-----------------------------------------------------------------------------

class AirportScene : public Framework::Scene
{
public:
    typedef std::shared_ptr<AirportScene> Ptr;

    AirportScene() {}
    virtual ~AirportScene() {}

    virtual void Initialise();

public: // Callbacks
    virtual void KeyAction(unsigned char key, bool keyDown, int x, int y);

private:

};

//-----------------------------------------------------------------------------

} // Application
