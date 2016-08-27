/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#include "MariposaYosemitePch.h"

#include "GroundPolygon.h"

namespace Application
{

//-----------------------------------------------------------------------------

Framework::WavefrontLoadOptions g_groundPolygonLoadOptions = { true };

//-----------------------------------------------------------------------------

GroundPolygon::GroundPolygon(std::string const& objFile, std::string const& textureFile, Framework::TextureManager::Ptr const& textureManager) :
    WavefrontObject(objFile, g_groundPolygonLoadOptions),
    m_textureHandle(0)
{
    Framework::TextureLoadOptions options;
    options.Linear          = true;
    options.Repeat          = true;
    options.GenerateMipMaps = true;
    options.DirectLoadDDS   = false;

    m_textureHandle = textureManager->GetTexture_SOIL(textureFile, std::move(options));
}

//-----------------------------------------------------------------------------

void GroundPolygon::Draw()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_textureHandle);

    WavefrontObject::Draw();

    glPopAttrib();
}

//-----------------------------------------------------------------------------

} // namespace Application
