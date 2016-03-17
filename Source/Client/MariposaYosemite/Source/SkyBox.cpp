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
    m_textureHandles[0] = (textureManager->GetTexture(R"(Resources\sb_up.bmp)", false, false));
    m_textureHandles[1] = (textureManager->GetTexture(R"(Resources\sb_down.bmp)", false, false));
    m_textureHandles[2] = (textureManager->GetTexture(R"(Resources\sb_south.bmp)", false, false));
    m_textureHandles[3] = (textureManager->GetTexture(R"(Resources\sb_west.bmp)", false, false));
    m_textureHandles[4] = (textureManager->GetTexture(R"(Resources\sb_north.bmp)", false, false));
    m_textureHandles[5] = (textureManager->GetTexture(R"(Resources\sb_east.bmp)", false, false));
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
