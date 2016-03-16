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
#include "GroundPolygon.h"
#include "Terrain.h"

namespace Application
{

//-----------------------------------------------------------------------------

class TexturedWavefrontObject : public Framework::WavefrontObject
{
public:
    TexturedWavefrontObject(std::string const& file, Framework::TextureManager::Ptr const& textureManager) :
        WavefrontObject(file, textureManager),
        m_textureHandle(textureManager->GetTexture(R"(Resources\ortho.bmp)"))
    {}

    virtual ~TexturedWavefrontObject() {}

    virtual void Draw()
    {
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glPushMatrix();

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, m_textureHandle);

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glVertexPointer(3, GL_FLOAT, 8 * sizeof(GLfloat), m_data.data());
        glTexCoordPointer(2, GL_FLOAT, 8 * sizeof(GLfloat), m_data.data() + 3);
        glNormalPointer(GL_FLOAT, 8 * sizeof(GLfloat), m_data.data() + 5);

        glDrawArrays(GL_TRIANGLES, 0, GetNumVertices());

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);

        glEnable(GL_DEPTH_TEST);
        glDisable(GL_TEXTURE_2D);

        glPopMatrix();
        glPopAttrib();
    }

private:
    GLuint m_textureHandle;
};

//-----------------------------------------------------------------------------

void AirportScene::Initialise()
{
    // Standard objects
    m_objects.push_back(std::make_shared<Application::Terrain>(m_environment->GetTextureManager()));
    m_objects.push_back(std::make_shared<TexturedWavefrontObject>(R"(Resources\airport-base.obj)", m_environment->GetTextureManager()));

    m_objects.push_back(std::make_shared<J3Aircraft>(m_camera));

    // Ground polygons/decals
    m_groundPolygons.push_back(std::make_shared<TexturedWavefrontObject>(R"(Resources\airport-base-flatten.obj)", m_environment->GetTextureManager()));
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
        case 'P':
        case 'p':
            printf("Eye Position: %s\r\n", m_camera->GetEyePosition().ToString().c_str());
            break;
        case 'O':
        case 'o':
            auto cub = std::dynamic_pointer_cast<J3Aircraft>(m_objects.back());
            cub->ENABLE_EPIC_MODE = !cub->ENABLE_EPIC_MODE;
            break;
        }
    }
}

//-----------------------------------------------------------------------------

} // namespace Application
