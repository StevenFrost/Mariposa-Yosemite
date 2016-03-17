/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#pragma once

#include <Framework/DisplayableObject.h>
#include <Framework/TextureManager.h>

#include <GL/freeglut.h>

namespace Application
{

//-----------------------------------------------------------------------------

class SkyBox : public Framework::DisplayableObject
{
public:
    SkyBox(Framework::TextureManager::Ptr const& textureManager);
    virtual ~SkyBox() {}

    virtual void Draw();

private:
    GLuint m_textureHandles[6];
};

//-----------------------------------------------------------------------------

} // namespace Application
