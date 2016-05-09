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

#include "CockpitCamera.h"
#include "Hangar.h"
#include "OrbitCamera.h"
#include "SkyBox.h"
#include "Terrain.h"
#include "TopDownCamera.h"
#include "TrackingCamera.h"

namespace Application
{

//-----------------------------------------------------------------------------

AirportScene::AirportScene(Environment::Ptr const& environment) :
    m_environment(environment),
    m_selectedObject(nullptr)
{}

//-----------------------------------------------------------------------------

void AirportScene::Initialise()
{
    auto sun = std::make_shared<Framework::Light>(GL_LIGHT0, false);
    sun->SetPosition(vec3(-3000.0f, 3000.0f, -3000.0f));
    sun->SetAttenuationLinear(0.05f);
    //sun->SetAmbient(vec4(0.1f, 0.1f, 0.1f, 1.0f));
    //sun->SetDiffuse(vec4(0.1f, 0.1f, 0.1f, 1.0f));
    //sun->SetSpecular(vec4(0.1f, 0.1f, 0.1f, 0.1f));

    m_aircraft = std::make_shared<Aircraft>();

    auto roamingCamera = std::make_shared<Framework::Camera>();
    auto orbitCamera = std::make_shared<OrbitCamera>(m_aircraft);
    auto cockpitCamera = std::make_shared<CockpitCamera>(m_aircraft);
    auto topDownCamera = std::make_shared<TopDownCamera>(m_aircraft);
    auto trackingCamera = std::make_shared<TrackingCamera>(m_aircraft);

    auto airportBaseFlatten = std::make_shared<GroundPolygon>(R"(Resources\airport-base-flatten.obj)", R"(Resources\orthoimagery.dds)", m_environment->GetTextureManager());
    auto groundpolyBase = std::make_shared<GroundPolygon>(R"(Resources\groundpoly-base.obj)", R"(Resources\asphalt.png)", m_environment->GetTextureManager());
    auto groundpolyColour = std::make_shared<GroundPolygon>(R"(Resources\groundpoly-colour.obj)", R"(Resources\groundpoly-colour.dds)", m_environment->GetTextureManager());
    auto groundpolyDetails1 = std::make_shared<GroundPolygon>(R"(Resources\groundpoly-details-1.obj)", R"(Resources\markings.dds)", m_environment->GetTextureManager());

    // General 3D Objects
    m_objects.push_back(std::make_shared<SkyBox>(m_environment->GetTextureManager()));
    m_objects.push_back(std::make_shared<Terrain>(m_environment->GetTextureManager()));
    m_objects.push_back(m_aircraft);

    // Lights
    m_objects.push_back(sun);

    // User Controlled Objects
    m_selectableObjects.push_back(std::make_shared<THangar>(vec3(31.277f, 0.0f, 121.099f), -14.0f, m_environment->GetTextureManager()));
    m_selectableObjects.push_back(std::make_shared<THangar>(vec3(27.773f, 0.0f, 135.265f), -14.0f, m_environment->GetTextureManager()));
    m_selectableObjects.push_back(std::make_shared<THangar>(vec3(18.667f, 0.0f, 110.459f), 166.0f, m_environment->GetTextureManager()));
    m_selectableObjects.push_back(std::make_shared<THangar>(vec3(15.191f, 0.0f, 124.403f), 166.0f, m_environment->GetTextureManager()));
    m_selectableObjects.push_back(std::make_shared<THangar>(vec3(11.694f, 0.0f, 138.426f), 166.0f, m_environment->GetTextureManager()));
    m_selectableObjects.push_back(std::make_shared<THangar>(vec3(-5.174f, 0.0f, 99.344f), -14.0f, m_environment->GetTextureManager()));
    m_selectableObjects.push_back(std::make_shared<THangar>(vec3(-17.717f, 0.0f, 89.07f), 166.0f, m_environment->GetTextureManager()));
    m_selectableObjects.push_back(std::make_shared<THangar>(vec3(-21.127f, 0.0f, 102.746f), 166.0f, m_environment->GetTextureManager()));
    m_selectableObjects.push_back(std::make_shared<THangar>(vec3(-32.506f, 0.0f, 128.012f), 166.0f, m_environment->GetTextureManager()));
    m_selectableObjects.push_back(std::make_shared<THangar>(vec3(-53.637f, 0.0f, 124.161f), -14.0f, m_environment->GetTextureManager()));
    m_selectableObjects.push_back(std::make_shared<THangar>(vec3(-47.405f, 0.0f, 99.517f), -14.0f, m_environment->GetTextureManager()));

    // Cameras
    m_cameras.insert(std::make_pair(CameraType::Roaming, roamingCamera));
    m_cameras.insert(std::make_pair(CameraType::Orbit, orbitCamera));
    m_cameras.insert(std::make_pair(CameraType::Cockpit, cockpitCamera));
    m_cameras.insert(std::make_pair(CameraType::TopDown, topDownCamera));
    m_cameras.insert(std::make_pair(CameraType::Tracking, trackingCamera));

    // Ground polygons (Rendered in order, last inserted element appears on top)
    m_groundPolygons.push_back(airportBaseFlatten);
    m_groundPolygons.push_back(groundpolyBase);
    m_groundPolygons.push_back(groundpolyDetails1);
    m_groundPolygons.push_back(groundpolyColour);

    m_camera = roamingCamera;
    AttachProjectionListener();
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

    for (size_t i = 0; i < m_selectableObjects.size(); ++i)
    {
        auto& object = m_selectableObjects.at(i);
        glLoadName(i + 1);
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

void AirportScene::Update(uint32_t frameTimeDelta)
{
    Scene::Update(frameTimeDelta);

    if (m_selectedObject != nullptr)
    {
        m_selectedObject->Update(frameTimeDelta);
    }
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
        case '5':
            m_camera->OnProjectionChanged = nullptr;
            m_camera = m_cameras.find(CameraType::Tracking)->second;
            AttachProjectionListener();
            Reshape(m_width, m_height);
            break;
        case 'L':
        case 'l':
            m_aircraft->SetLightsEnabled(!m_aircraft->GetLightsEnabled());
            break;
        }
    }
}

//-----------------------------------------------------------------------------

void AirportScene::SpecialKeyAction(int key, bool keyDown, int x, int y)
{
    Scene::SpecialKeyAction(key, keyDown, x, y);

    if (m_selectedObject != nullptr)
    {
        m_selectedObject->SpecialKeyAction(key, keyDown, x, y);
    }
}

//-----------------------------------------------------------------------------

void AirportScene::MouseAction(int button, bool mouseDown, int x, int y)
{
    Scene::MouseAction(button, mouseDown, x, y);

    if (mouseDown && button == GLUT_RIGHT_BUTTON)
    {
        GLuint buff[64] = { 0 };
        GLint hits, view[4];

        glSelectBuffer(64, buff);

        glGetIntegerv(GL_VIEWPORT, view);
        glRenderMode(GL_SELECT);

        glInitNames();
        glPushName(0);

        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
            glLoadIdentity();

            gluPickMatrix(x, m_height - y - 1.0, 1.0, 1.0, view);
            m_camera->Projection(m_width, m_height);

            glMatrixMode(GL_MODELVIEW);
            Draw();
            glMatrixMode(GL_PROJECTION);
        glPopMatrix();

        hits = glRenderMode(GL_RENDER);

        m_selectedObject = nullptr;
        for (int i = 0; i < hits; ++i)
        {
            if (m_selectedObject == nullptr && buff[i * 4 + 3] != 0)
            {
                m_selectedObject = m_selectableObjects.at(buff[i * 4 + 3] - 1);
            }
        }

        glMatrixMode(GL_MODELVIEW);
        glPopName();
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
