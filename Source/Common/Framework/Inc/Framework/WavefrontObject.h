/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#pragma once

#include <memory>
#include <string>
#include <vector>

#include <Framework/DisplayableObject.h>
#include <Framework/TextureManager.h>

namespace Framework
{

//-----------------------------------------------------------------------------

struct WavefrontMaterial
{
    typedef std::shared_ptr<WavefrontMaterial> Ptr;

    WavefrontMaterial(std::string const& name) :
        Name(name),
        Transparency(0.0f)
    {}

    std::string Name;

    float Transparency;

    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
    vec3 Emissive;
};

//-----------------------------------------------------------------------------

class WavefrontMesh : public DisplayableObject
{
public:
    typedef std::shared_ptr<WavefrontMesh> Ptr;

    WavefrontMesh(std::string const& name);
    virtual ~WavefrontMesh() {}

    virtual void Draw();

    void SetData(std::vector<float> && data, uint32_t numVertices, WavefrontMaterial::Ptr const& material, bool normals, bool texCoords);

private:
    std::string            m_name;
    std::vector<float>     m_data;
    WavefrontMaterial::Ptr m_material;

    bool     m_normals;
    bool     m_texCoords;
    uint32_t m_numVertices;
};

//-----------------------------------------------------------------------------

class WavefrontObject : public DisplayableObject
{
public:
    typedef std::shared_ptr<WavefrontObject> Ptr;

    WavefrontObject(std::string const& objFile, TextureManager::Ptr const& textureManager);

    virtual void Draw();

private:
    void Read_OBJ();
    void Read_MTL(std::string const& fileName);

protected:
    TextureManager::Ptr m_textureManager;

    std::string m_file;

    std::vector<WavefrontMesh::Ptr>               m_meshes;
    std::map<std::string, WavefrontMaterial::Ptr> m_materials;
};

//-----------------------------------------------------------------------------

class TexturedWavefrontObject : public Framework::WavefrontObject
{
public:
    TexturedWavefrontObject(std::string const& file, Framework::TextureManager::Ptr const& textureManager) :
        WavefrontObject(file, textureManager),
        m_textureHandle(textureManager->GetTexture_SOIL(R"(Resources\ortho.jpg)"))
    {}

    virtual ~TexturedWavefrontObject() {}

    virtual void Draw();

private:
    GLuint m_textureHandle;
};

//-----------------------------------------------------------------------------

} // namespace Framework
