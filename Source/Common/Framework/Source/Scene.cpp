/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#include "FrameworkPch.h"

#include <Framework/Scene.h>

#include <memory>

#include <Framework/Animation.h>
#include <Framework/AnimatedWavefrontObject.h>
#include <GL/freeglut.h>

namespace Framework
{

//-----------------------------------------------------------------------------

Scene::Scene() :
    m_camera(std::make_shared<Camera>())
{}

//-----------------------------------------------------------------------------

void Scene::Initialise() {}

//-----------------------------------------------------------------------------

void Scene::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    m_camera->Look();

    for (auto& object : m_objects)
    {
        object->Draw();
    }
}

//-----------------------------------------------------------------------------

void Scene::Update(uint32_t frameTimeDelta)
{
    m_camera->Update(frameTimeDelta);

    for (auto& object : m_objects)
    {
        auto animation = std::dynamic_pointer_cast<Animation>(object);
        if (animation != nullptr)
        {
            animation->Update(frameTimeDelta);
        }

        auto animation2 = std::dynamic_pointer_cast<AnimatedWavefrontObject>(object);
        if (animation2 != nullptr)
        {
            animation2->Update(frameTimeDelta);
        }
    }
}

//-----------------------------------------------------------------------------

void Scene::KeyAction(unsigned char key, bool keyDown, int x, int y)
{
    m_camera->KeyAction(key, keyDown, x, y);
}

//-----------------------------------------------------------------------------

void Scene::SpecialKeyAction(int key, bool keyDown, int x, int y)
{
    m_camera->SpecialKeyAction(key, keyDown, x, y);
}

//-----------------------------------------------------------------------------

void Scene::MouseAction(int button, bool mouseDown, int x, int y)
{
    m_camera->MouseAction(button, mouseDown, x, y);
}

//-----------------------------------------------------------------------------

void Scene::MouseMotion(int x, int y)
{
    m_camera->MouseMotion(x, y);
}

//-----------------------------------------------------------------------------

void Scene::PassiveMouseMotion(int x, int y)
{
    m_camera->PassiveMouseMotion(x, y);
}

//-----------------------------------------------------------------------------

} // namespace Framework
