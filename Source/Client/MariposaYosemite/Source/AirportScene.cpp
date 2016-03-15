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

#include "Terrain.h"

namespace Application
{

//-----------------------------------------------------------------------------

void AirportScene::Initialise()
{
    // Standard objects
    m_objects.push_back(std::make_shared<Application::Terrain>(m_environment->GetTextureManager()));
    m_objects.push_back(std::make_shared<Framework::WavefrontObject>(
        R"(Resources\buildings.obj)",
        m_environment->GetTextureManager())
    );

    // Ground polygons/decals
    m_groundPolygons.push_back(std::make_shared<GroundPolygon>(
        R"(Resources\runway.obj)",
        m_environment->GetTextureManager())
    );
}

//-----------------------------------------------------------------------------

void AirportScene::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    m_camera->Look();

#ifdef ENABLE_DECAL_DRAW_MODE
    glDepthMask(GL_TRUE);
    glStencilFunc(GL_ALWAYS, 0, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
#endif // ENABLE_DECAL_DRAW_MODE
    for (auto& object : m_objects)
    {
        object->Draw();
    }

#ifdef ENABLE_DECAL_DRAW_MODE
    glDepthMask(GL_FALSE);
    glStencilFunc(GL_NOTEQUAL, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
#endif // ENABLE_DECAL_DRAW_MODE
    for (auto& groundPolygon : m_groundPolygons)
    {
        groundPolygon->Draw();
    }

#ifdef ENABLE_DECAL_DRAW_MODE
    glDepthMask(GL_TRUE);
#endif // ENABLE_DECAL_DRAW_MODE
}

//-----------------------------------------------------------------------------

void AirportScene::KeyAction(unsigned char key, bool keyDown, int x, int y)
{
    Scene::KeyAction(key, keyDown, x, y);

    if (keyDown)
    {
        switch (key)
        {
        case 'P':
        case 'p':
            printf("Eye Position: %s\r\n", m_camera->GetEyePosition().ToString().c_str());
            break;
        }
    }
}

//-----------------------------------------------------------------------------

} // namespace Application
