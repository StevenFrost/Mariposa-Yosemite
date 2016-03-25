/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#pragma once

#include <map>
#include <memory>
#include <vector>

#include <Framework/Camera.h>
#include <Framework/Scene.h>
#include <Framework/WavefrontObject.h>

#include "Environment.h"
#include "GroundPolygon.h"

namespace Application
{

//-----------------------------------------------------------------------------

enum class CameraType
{
    Roaming,
    Orbit,
    Cockpit,
    TopDown
};

//-----------------------------------------------------------------------------

class AirportScene : public Framework::Scene, public std::enable_shared_from_this<AirportScene>
{
public:
    typedef std::shared_ptr<AirportScene> Ptr;

    AirportScene(Environment::Ptr const& environment);
    virtual ~AirportScene() {}

    virtual void Initialise();
    virtual void Draw();
    virtual void Update(uint32_t frameTimeDelta);

public: // Callbacks
    virtual void KeyAction(unsigned char key, bool keyDown, int x, int y);
    virtual void SpecialKeyAction(int key, bool keyDown, int x, int y);

    virtual void MouseAction(int button, bool mouseDown, int x, int y);

private:
    void AttachProjectionListener();
    void CameraProjectionChanged();

private:
    Environment::Ptr m_environment;

    std::vector<GroundPolygon::Ptr>              m_groundPolygons;
    std::map<CameraType, Framework::Camera::Ptr> m_cameras;

    std::vector<Framework::UserControlledDisplayableObject::Ptr> m_selectableObjects;
    Framework::UserControlledDisplayableObject::Ptr              m_selectedObject;
};

//-----------------------------------------------------------------------------

} // namespace Application
