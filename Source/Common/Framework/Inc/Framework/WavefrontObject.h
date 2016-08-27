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

struct WavefrontLoadOptions
{
    // Groups all object submeshes into one buffer, resulting in one draw call
    // for the entire object rather than one for each mesh.
    bool BatchMeshes;
};

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

// This class has the ability to load, parse and render Wavefront OBJ files. It
// it assumed that all meshes have been triangulated and the object has at most
// one texture. For objects without a texture the material properties stored in
// the MTL material library are used.
//
// By default, submeshes are not batched together which results in one draw
// call per object mesh. This behaviour can be changed via the
// WavefrontLoadOptions structure and individual meshes can be handled in one
// group. This is not default behaviour as submeshes often have unique
// materials that need their own draw call.
//
// Since Wavefront OBJ files do not encode animation no implementation is
// provided in this class. However, animation can be achieved by overloading
// the Update function and adjusting submeshes accordingly. In addition, the
// vector container will need to be replaced with a tree representing the
// object mesh hierarchy. Again, this information is not encoded in the OBJ
// file itself so an implementation has not been provided.
//
// It is assumed that the texture to be used by the object is already bound to
// the OpenGL context.
class WavefrontObject : public DisplayableObject
{
public:
    typedef std::shared_ptr<WavefrontObject> Ptr;

    WavefrontObject(std::string const& objFile);
    WavefrontObject(std::string const& objFile, WavefrontLoadOptions const& options);

    virtual ~WavefrontObject() {}

    virtual void Draw();

private:
    void Read_OBJ();
    void Read_MTL(std::string const& fileName);

protected:
    std::string          m_file;
    WavefrontLoadOptions m_options;

    std::vector<WavefrontMesh::Ptr>               m_meshes;
    std::map<std::string, WavefrontMaterial::Ptr> m_materials;
};

//-----------------------------------------------------------------------------

} // namespace Framework
