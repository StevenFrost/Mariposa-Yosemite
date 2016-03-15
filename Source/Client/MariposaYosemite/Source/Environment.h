/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#pragma once

#include <memory>

#include <Framework/TextureManager.h>

namespace Application
{

//-----------------------------------------------------------------------------

class Environment
{
public:
    typedef std::shared_ptr<Environment> Ptr;

    Environment();
    virtual ~Environment() {}

    Framework::TextureManager::Ptr GetTextureManager() const;

private:
    Framework::TextureManager::Ptr m_textureManager;
};

//-----------------------------------------------------------------------------

} // namespace Application
