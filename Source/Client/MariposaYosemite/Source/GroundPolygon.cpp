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

GroundPolygon::GroundPolygon(std::string const& objFile, Framework::TextureManager::Ptr const& textureManager) :
    WavefrontObject(objFile, textureManager)
{}

//-----------------------------------------------------------------------------

void GroundPolygon::Draw()
{
    glPushMatrix();
    glTranslatef(0.0f, 0.1f, 0.0f);
    WavefrontObject::Draw();
    glPopMatrix();
}

//-----------------------------------------------------------------------------

} // namespace Application
