/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#include "MariposaYosemitePch.h"

#include "SkyBox.h"

namespace Application
{

//-----------------------------------------------------------------------------

SkyBox::SkyBox(Framework::TextureManager::Ptr const& textureManager)
{
    Framework::TextureLoadOptions options;
    options.Linear          = false;
    options.Repeat          = false;
    options.GenerateMipMaps = false;
    options.DirectLoadDDS   = true;

    m_textureHandles[0] = textureManager->GetTexture_SOIL(R"(Resources\sb_up.dds)", options);
    m_textureHandles[1] = textureManager->GetTexture_SOIL(R"(Resources\sb_down.dds)", options);
    m_textureHandles[2] = textureManager->GetTexture_SOIL(R"(Resources\sb_south.dds)", options);
    m_textureHandles[3] = textureManager->GetTexture_SOIL(R"(Resources\sb_west.dds)", options);
    m_textureHandles[4] = textureManager->GetTexture_SOIL(R"(Resources\sb_north.dds)", options);
    m_textureHandles[5] = textureManager->GetTexture_SOIL(R"(Resources\sb_east.dds)", options);
}

//-----------------------------------------------------------------------------

void SkyBox::Draw()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPushMatrix();

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);

    double length = 10000.0;

    // Top
    glBindTexture(GL_TEXTURE_2D, m_textureHandles[0]);
    glBegin(GL_QUADS);
    glTexCoord2d(0.0, 1.0);
    glVertex3d(length, length, length);
    glTexCoord2d(1.0, 1.0);
    glVertex3d(-length, length, length);
    glTexCoord2d(1.0, 0.0);
    glVertex3d(-length, length, -length);
    glTexCoord2d(0.0, 0.0);
    glVertex3d(length, length, -length);
    glEnd();

    // Bottom
    glBindTexture(GL_TEXTURE_2D, m_textureHandles[1]);
    glBegin(GL_QUADS);
    glTexCoord2d(0.0, 1.0);
    glVertex3d(length, -length, length);
    glTexCoord2d(0.0, 0.0);
    glVertex3d(length, -length, -length);
    glTexCoord2d(1.0, 0.0);
    glVertex3d(-length, -length, -length);
    glTexCoord2d(1.0, 1.0);
    glVertex3d(-length, -length, length);
    glEnd();

    // South
    glBindTexture(GL_TEXTURE_2D, m_textureHandles[2]);
    glBegin(GL_QUADS);
    glTexCoord2d(0.0, 1.0);
    glVertex3d(length, length, length);
    glTexCoord2d(0.0, 0.0);
    glVertex3d(length, -length, length);
    glTexCoord2d(1.0, 0.0);
    glVertex3d(-length, -length, length);
    glTexCoord2d(1.0, 1.0);
    glVertex3d(-length, length, length);
    glEnd();

    // West
    glBindTexture(GL_TEXTURE_2D, m_textureHandles[3]);
    glBegin(GL_QUADS);
    glTexCoord2d(0.0, 1.0);
    glVertex3d(-length, length, length);
    glTexCoord2d(0.0, 0.0);
    glVertex3d(-length, -length, length);
    glTexCoord2d(1.0, 0.0);
    glVertex3d(-length, -length, -length);
    glTexCoord2d(1.0, 1.0);
    glVertex3d(-length, length, -length);
    glEnd();

    // North
    glBindTexture(GL_TEXTURE_2D, m_textureHandles[4]);
    glBegin(GL_QUADS);
    glTexCoord2d(0.0, 1.0);
    glVertex3d(length, length, -length);
    glTexCoord2d(1.0, 1.0);
    glVertex3d(-length, length, -length);
    glTexCoord2d(1.0, 0.0);
    glVertex3d(-length, -length, -length);
    glTexCoord2d(0.0, 0.0);
    glVertex3d(length, -length, -length);
    glEnd();

    // East
    glBindTexture(GL_TEXTURE_2D, m_textureHandles[5]);
    glBegin(GL_QUADS);
    glTexCoord2d(1.0, 1.0);
    glVertex3d(length, length, length);
    glTexCoord2d(0.0, 1.0);
    glVertex3d(length, length, -length);
    glTexCoord2d(0.0, 0.0);
    glVertex3d(length, -length, -length);
    glTexCoord2d(1.0, 0.0);
    glVertex3d(length, -length, length);
    glEnd();

    glPopMatrix();
    glPopAttrib();
}

//-----------------------------------------------------------------------------

} // namespace Application
