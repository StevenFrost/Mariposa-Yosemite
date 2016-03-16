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

} // namespace Application
