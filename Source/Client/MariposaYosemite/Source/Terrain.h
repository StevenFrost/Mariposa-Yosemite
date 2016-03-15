/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include <Framework/DisplayableObject.h>
#include <Framework/TextureManager.h>

namespace Application
{

//-----------------------------------------------------------------------------

class Terrain : public Framework::DisplayableObject
{
public:
    typedef std::shared_ptr<Terrain> Ptr;

    Terrain(Framework::TextureManager::Ptr const& textureManager);
    virtual ~Terrain();

    virtual void Draw();

private:
    void BuildHeightMapFromFile(std::string const& hgtFile);

    void LoadTerrainResources();
    void BuildDisplayList();
    uint16_t GetCorrectedHeightAt(uint16_t x, uint16_t y);

private:
    const uint16_t m_top    = 1696;
    const uint16_t m_bottom = 1983;
    const uint16_t m_left   = 3314;
    const uint16_t m_right  = 3601;

    const uint16_t m_tileWidth;
    const uint16_t m_tileHeight;

    Framework::TextureManager::Ptr m_textureManager;

    uint16_t** m_heightMap;
    GLuint     m_orthoTextureHandle;

    GLuint m_displayListHandle;
};

//-----------------------------------------------------------------------------

} // namespace Application