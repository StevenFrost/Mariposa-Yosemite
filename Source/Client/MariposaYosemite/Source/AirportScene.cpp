/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#include "MariposaYosemitePch.h"

#include "AirportScene.h"

#include <Framework/DisplayableObject.h>
#include <Framework/Light.h>
#include <Framework/Vector.h>
#include <Framework/WavefrontObject.h>
#include <GL/freeglut.h>

#include "Aircraft.h"
#include "CockpitCamera.h"
#include "GroundPolygon.h"
#include "OrbitCamera.h"
#include "SkyBox.h"
#include "Terrain.h"
#include "TopDownCamera.h"

namespace Application
{

//-----------------------------------------------------------------------------

AirportScene::AirportScene(Environment::Ptr const& environment) :
    m_environment(environment)
{}

//-----------------------------------------------------------------------------

void AirportScene::Initialise()
{
    auto skybox = std::make_shared<SkyBox>(m_environment->GetTextureManager());
    auto terrain = std::make_shared<Application::Terrain>(m_environment->GetTextureManager());
    auto airportBase = std::make_shared<Framework::TexturedWavefrontObject>(R"(Resources\airport-base.obj)", m_environment->GetTextureManager());
    auto buildings = std::make_shared<Framework::WavefrontObject>(R"(Resources\buildings.obj)", nullptr);
    auto aircraft = std::make_shared<Aircraft>();

    auto roamingCamera = std::make_shared<Framework::Camera>();
    auto orbitCamera = std::make_shared<OrbitCamera>(aircraft);
    auto cockpitCamera = std::make_shared<CockpitCamera>(aircraft);
    auto topDownCamera = std::make_shared<TopDownCamera>(aircraft);

    auto airportBaseFlatten = std::make_shared<Framework::TexturedWavefrontObject>(R"(Resources\airport-base-flatten.obj)", m_environment->GetTextureManager());
    auto runway = std::make_shared<GroundPolygon>(R"(Resources\runway.obj)", m_environment->GetTextureManager());


    m_objects.push_back(skybox);
    m_objects.push_back(terrain);
    m_objects.push_back(airportBase);
    m_objects.push_back(buildings);
    m_objects.push_back(aircraft);

    m_cameras.insert(std::make_pair(CameraType::Roaming, roamingCamera));
    m_cameras.insert(std::make_pair(CameraType::Orbit, orbitCamera));
    m_cameras.insert(std::make_pair(CameraType::Cockpit, cockpitCamera));
    m_cameras.insert(std::make_pair(CameraType::TopDown, topDownCamera));

    m_groundPolygons.push_back(airportBaseFlatten);
    m_groundPolygons.push_back(runway);
}

//-----------------------------------------------------------------------------

void AirportScene::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    m_camera->Look();

    glDepthMask(GL_TRUE);
    glStencilFunc(GL_ALWAYS, 0, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    for (auto& object : m_objects)
    {
        object->Draw();
    }

    glDepthMask(GL_FALSE);
    glStencilFunc(GL_NOTEQUAL, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    for (auto& groundPolygon : m_groundPolygons)
    {
        groundPolygon->Draw();
    }

    glDepthMask(GL_TRUE);
}

//-----------------------------------------------------------------------------

void AirportScene::KeyAction(unsigned char key, bool keyDown, int x, int y)
{
    Scene::KeyAction(key, keyDown, x, y);

    if (keyDown)
    {
        switch (key)
        {
        case '1':
            m_camera->OnProjectionChanged = nullptr;
            m_camera = m_cameras.find(CameraType::Roaming)->second;
            AttachProjectionListener();
            Reshape(m_width, m_height);
            break;
        case '2':
            m_camera->OnProjectionChanged = nullptr;
            m_camera = m_cameras.find(CameraType::Orbit)->second;
            AttachProjectionListener();
            Reshape(m_width, m_height);
            break;
        case '3':
            m_camera->OnProjectionChanged = nullptr;
            m_camera = m_cameras.find(CameraType::Cockpit)->second;
            AttachProjectionListener();
            Reshape(m_width, m_height);
            break;
        case '4':
            m_camera->OnProjectionChanged = nullptr;
            m_camera = m_cameras.find(CameraType::TopDown)->second;
            AttachProjectionListener();
            Reshape(m_width, m_height);
            break;
        }
    }
}

//-----------------------------------------------------------------------------

void AirportScene::AttachProjectionListener()
{
    auto weakThis = std::weak_ptr<AirportScene>(shared_from_this());
    m_camera->OnProjectionChanged = [weakThis]()
    {
        if (weakThis.expired())
        {
            return;
        }
        auto strongThis = weakThis.lock();
        strongThis->Reshape(strongThis->m_width, strongThis->m_height);
    };
}

//-----------------------------------------------------------------------------

void AirportScene::CameraProjectionChanged()
{
    Reshape(m_width, m_height);
}

//-----------------------------------------------------------------------------

} // namespace Application
