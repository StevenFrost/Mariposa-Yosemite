/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#include "MariposaYosemitePch.h"

#include "Terrain.h"

#include <fstream>
#include <iostream>
#include <string>

#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/GL.h>
#include <GL/GLU.h>

namespace Application
{

//-----------------------------------------------------------------------------

const uint16_t SRTM_1 = 3601;

//-----------------------------------------------------------------------------

vec3 CalculateTriangleNormal(vec3 const& a, vec3 const& b, vec3 const& c)
{
    vec3 result = (b - a).Cross(c - a);
    result.Normalize();
    return result;
}

//-----------------------------------------------------------------------------

Terrain::Terrain(Framework::TextureManager::Ptr const& textureManager) :
    m_tileWidth(m_right - m_left),
    m_tileHeight(m_bottom - m_top),
    m_textureManager(textureManager)
{
    LoadTerrainResources();
    BuildDisplayList();
}

//-----------------------------------------------------------------------------

Terrain::~Terrain()
{
    glDeleteLists(m_displayListHandle, 1);
}

//-----------------------------------------------------------------------------

void Terrain::Draw()
{
#ifdef BRUTE_FORCE_TERRAIN
    float scale = 0.05f;
    float frac = 1.0f / static_cast<float>(m_tileHeight);
    float halfHeight = m_tileHeight / 2.0f;
    float halfWidth = m_tileWidth / 2.0f;

    halfHeight = 0.0f;
    halfWidth = 0.0f;

    glPushMatrix();

    glTranslatef(0.0f, -70.0f, 0.0f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_orthoTextureHandle);

    glBegin(GL_QUADS);
    for (uint16_t i = 0; i < m_tileHeight - 1; ++i)
    {
        for (uint16_t j = 0; j < m_tileWidth - 1; ++j)
        {
            glTexCoord2f(i * frac, j * frac);
            glVertex3f(
                static_cast<float>(i - halfHeight),
                static_cast<float>(m_heightMap[i][j]) * scale,
                static_cast<float>(-j + halfWidth)
            );

            glTexCoord2f((i + 1) * frac, j * frac);
            glVertex3f(
                static_cast<float>((i + 1) - halfHeight),
                static_cast<float>(m_heightMap[i + 1][j]) * scale,
                static_cast<float>(-j + halfWidth)
            );

            glTexCoord2f((i + 1) * frac, (j + 1) * frac);
            glVertex3f(
                static_cast<float>((i + 1) - halfHeight),
                static_cast<float>(m_heightMap[i + 1][j + 1]) * scale,
                static_cast<float>(-(j + 1) + halfWidth)
            );

            glTexCoord2f(i * frac, (j + 1) * frac);
            glVertex3f(
                static_cast<float>(i - halfHeight),
                static_cast<float>(m_heightMap[i][j + 1]) * scale,
                static_cast<float>(-(j + 1) + halfWidth)
            );
        }
    }
    glEnd();
    glPopMatrix();
#endif // BRUTE_FORCE_TERRAIN

    glCallList(m_displayListHandle);
}

//-----------------------------------------------------------------------------

void Terrain::BuildHeightMapFromFile(std::string const& hgtFile)
{
    const uint8_t BYTES_PER_CELL = 2;

    std::ifstream file(hgtFile, std::ios::in | std::ios::binary);
    if (!file)
    {
        std::cout << "Error opening HGT file '" << hgtFile << "'." << std::endl;
        return;
    }

    // Seek to the start of the region to parse
    file.seekg((SRTM_1 * (SRTM_1 - m_bottom)) * BYTES_PER_CELL, file.beg);

    unsigned char buffer[2];
    for (uint16_t i = 0; i < m_bottom - m_top; ++i)
    {
        // Seek to the next line
        file.seekg(m_left * BYTES_PER_CELL, file.cur);
        for (uint16_t j = 0; j < m_right - m_left; ++j)
        {
            if (!file.read(reinterpret_cast<char*>(buffer), sizeof(buffer)))
            {
                std::cout << "Error reading HGT file '" << hgtFile << "'." << std::endl;
                return;
            }
            m_heightMap[i][j] = (buffer[0] << 8) | buffer[1];

            if (m_heightMap[i][j] > 64000)
            {
                m_heightMap[i][j] = 0;
            }
        }
    }
}

//-----------------------------------------------------------------------------

void Terrain::LoadTerrainResources()
{
    m_heightMap = new uint16_t*[m_tileHeight];
    for (uint16_t i = 0; i < m_tileHeight; ++i)
    {
        m_heightMap[i] = new uint16_t[m_tileWidth];
    }

    BuildHeightMapFromFile(R"(Resources\N37W121.hgt)");
    m_orthoTextureHandle = m_textureManager->GetTexture(R"(Resources\ortho.bmp)");
}

//-----------------------------------------------------------------------------

void Terrain::BuildDisplayList()
{
    m_displayListHandle = glGenLists(1);
    glNewList(m_displayListHandle, GL_COMPILE);

    float scale = 1.0f;
    float texCoordCellWidth = 1.0f / static_cast<float>(m_tileHeight);
    float halfHeight = m_tileHeight / 2.0f;
    float halfWidth = m_tileWidth / 2.0f;

    glPushMatrix();

    glScalef(30.0f, 1.0f, 30.0f);
    glTranslatef(0.0f, -680.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_orthoTextureHandle);

    glBegin(GL_TRIANGLES);
    for (uint16_t i = 0; i < m_tileHeight - 1; ++i)
    {
        for (uint16_t j = 0; j < m_tileWidth - 1; ++j)
        {
            // Triangle 1
            {
                vec3 a(j - halfHeight, GetCorrectedHeightAt(i, j) * scale, i - halfWidth);
                vec3 b(j - halfWidth, GetCorrectedHeightAt(i + 1, j) * scale, (i + 1) - halfHeight);
                vec3 c((j + 1) - halfWidth, GetCorrectedHeightAt(i, j + 1) * scale, i - halfHeight);
                
                vec3 n = CalculateTriangleNormal(a, b, c);
                glNormal3f(n.x, n.y, n.z);

                glTexCoord2f(i * texCoordCellWidth, j * texCoordCellWidth);
                glVertex3f(a.x, a.y, a.z);

                glTexCoord2f((i + 1) * texCoordCellWidth, j * texCoordCellWidth);
                glVertex3f(b.x, b.y, b.z);

                glTexCoord2f(i * texCoordCellWidth, (j + 1) * texCoordCellWidth);
                glVertex3f(c.x, c.y, c.z);
            }

            // Triangle 2
            {
                vec3 a(j - halfWidth, GetCorrectedHeightAt(i + 1, j) * scale, (i + 1) - halfHeight);
                vec3 b((j + 1) - halfWidth, GetCorrectedHeightAt(i + 1, j + 1) * scale, (i + 1) - halfHeight);
                vec3 c((j + 1) - halfWidth, GetCorrectedHeightAt(i, j + 1) * scale, i - halfHeight);

                vec3 n = CalculateTriangleNormal(a, b, c);
                glNormal3f(n.x, n.y, n.z);

                glTexCoord2f((i + 1) * texCoordCellWidth, j * texCoordCellWidth);
                glVertex3f(a.x, a.y, a.z);

                glTexCoord2f((i + 1) * texCoordCellWidth, (j + 1) * texCoordCellWidth);
                glVertex3f(b.x, b.y, b.z);

                glTexCoord2f(i * texCoordCellWidth, (j + 1) * texCoordCellWidth);
                glVertex3f(c.x, c.y, c.z);
            }
        }
    }
    glEnd();
    glPopMatrix();
    glEndList();
}

//-----------------------------------------------------------------------------

uint16_t Terrain::GetCorrectedHeightAt(uint16_t x, uint16_t y)
{
    if (x > 138 && x < 152 && y > 120 && y < 170)
    {
        return 680;
    }
    return m_heightMap[x][y];
}

//-----------------------------------------------------------------------------

} // namespace Application
