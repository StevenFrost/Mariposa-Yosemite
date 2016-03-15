/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#include "FrameworkPch.h"

#include <Framework/TextureManager.h>

#include <iostream>
#include <Windows.h>

namespace Framework
{

//-----------------------------------------------------------------------------

TextureManager::~TextureManager(void)
{
    for (auto& texture : m_textures)
    {
        glDeleteTextures(1, &texture.second);
    }
}

//-----------------------------------------------------------------------------

GLuint TextureManager::GetTexture(std::string const& fileName, bool generateMips)
{
    auto it = m_textures.find(fileName);
    if (it != m_textures.end())
    {
        return it->second;
    }

    FILE *file = nullptr;
    fopen_s(&file, fileName.c_str(), "r");
    if (file == nullptr)
    {
        std::cout << "Error: Failed to open '" << fileName << "'." << std::endl;
        return 0;
    }

    BITMAPFILEHEADER fileHeader;
    fread(&fileHeader, 14, 1, file);
    if (fileHeader.bfType != 0x4D42)
    {
        std::cout << "Error: Trying to load '" << fileName <<
            "'. It is in an invalid bitmap format." << std::endl;

        fclose(file);
        return 0;
    }

    BITMAPINFOHEADER infoHeader;
    fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, file);
    if (infoHeader.biBitCount < 24)
    {
        std::cout << "Error: Trying to load '" << fileName << std::endl <<
            "The file is not in RGB or RGBA format." << std::endl <<
            "It may be in grayscale format, open it in an image editor of your choice and change the image mode to RGB or RGBA." << std::endl;

        fclose(file);
        return 0;
    }

    fseek(file, fileHeader.bfOffBits, SEEK_SET);

    auto pixelBuffer = new unsigned char[infoHeader.biWidth * infoHeader.biHeight * (infoHeader.biBitCount / 8)];
    fread(pixelBuffer, sizeof(unsigned char), infoHeader.biWidth * infoHeader.biHeight * (infoHeader.biBitCount / 8), file);

    // If texture is in ABGR format swizzle it into RGBA for OpenGL
    if (infoHeader.biBitCount == 32)
    {
        for (int i = 0; i < infoHeader.biWidth * infoHeader.biHeight; ++i)
        {
            unsigned char c = pixelBuffer[i * 4];
            pixelBuffer[i * 4] = pixelBuffer[i * 4 + 3];
            pixelBuffer[i * 4 + 3] = c;

            c = pixelBuffer[i * 4 + 1];
            pixelBuffer[i * 4 + 1] = pixelBuffer[i * 4 + 2];
            pixelBuffer[i * 4 + 2] = c;
        }
    }

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);

    GLuint handle;
    glGenTextures(1, &handle);
    glBindTexture(GL_TEXTURE_2D, handle);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    if (generateMips)
    {
        gluBuild2DMipmaps(
            GL_TEXTURE_2D,
            3,
            infoHeader.biWidth,
            infoHeader.biHeight,
            infoHeader.biBitCount == 32 ? GL_RGBA : GL_BGR_EXT,
            GL_UNSIGNED_BYTE,
            pixelBuffer
        );
    }
    else
    {
        glTexImage2D(GL_TEXTURE_2D, 0,
            infoHeader.biBitCount == 32 ? GL_RGBA : GL_RGB,
            infoHeader.biWidth,
            infoHeader.biHeight,
            0,
            infoHeader.biBitCount == 32 ? GL_RGBA : GL_BGR_EXT,
            GL_UNSIGNED_BYTE,
            pixelBuffer
        );
    }

    glDisable(GL_TEXTURE_2D);

    delete[] pixelBuffer;
    fclose(file);

    m_textures.insert(m_textures.end(), std::make_pair(fileName, handle));
    return handle;
}

//-----------------------------------------------------------------------------

} // namespace Framework