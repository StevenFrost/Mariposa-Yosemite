/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#include "MariposaYosemitePch.h"

#include "Environment.h"

namespace Application
{

//-----------------------------------------------------------------------------

Environment::Environment() :
    m_textureManager(std::make_shared<Framework::TextureManager>())
{}

//-----------------------------------------------------------------------------

Framework::TextureManager::Ptr Environment::GetTextureManager() const
{
    return m_textureManager;
}

//-----------------------------------------------------------------------------

} // namespace Application
