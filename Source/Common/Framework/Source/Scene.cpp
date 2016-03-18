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
    m_camera(std::make_shared<Camera>()),
    m_width(800),
    m_height(600)
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

    m_camera->Update(frameTimeDelta);
}

//-----------------------------------------------------------------------------

void Scene::Reshape(int32_t width, int32_t height)
{
    m_width = width;
    m_height = height;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    m_camera->Projection(width, height);

    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height));
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
