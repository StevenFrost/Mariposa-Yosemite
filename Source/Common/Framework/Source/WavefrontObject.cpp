/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#include "FrameworkPch.h"

#include <Framework/WavefrontObject.h>

#include <fstream>
#include <string>
#include <vector>

#include <Framework/Vector.h>

namespace Framework
{

//-----------------------------------------------------------------------------

template <class T>
std::vector<T> Split(T const& s, T const& d)
{
    T::size_type startPos = 0;
    T::size_type endPos = s.find(d, startPos);

    std::vector<T> result;

    while (endPos != T::npos)
    {
        result.push_back(s.substr(startPos, endPos - startPos));
        startPos = endPos + d.size();

        endPos = s.find(d, startPos);
    }
    result.push_back(s.substr(startPos, s.size() - startPos));
    return result;
}

//-----------------------------------------------------------------------------

WavefrontMesh::WavefrontMesh(std::string const& name) :
    m_name(name),
    m_normals(false),
    m_texCoords(false)
{}

//-----------------------------------------------------------------------------

void WavefrontMesh::Draw()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPushMatrix();

    if (!m_texCoords)
    {
        glDisable(GL_TEXTURE_2D);
        if (m_material != nullptr)
        {
            if (m_material->Transparency != 1.0)
            {
                glDepthMask(GL_FALSE);
            }
            glColor4f(m_material->Diffuse.x, m_material->Diffuse.y, m_material->Diffuse.z, m_material->Transparency);
        }
        else
        {
            glColor3f(0.608f, 0.608f, 0.608f);
        }
    }

    GLsizei stride = 3;
    if (m_texCoords) { stride += 2; }
    if (m_normals)   { stride += 3; }

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, stride * sizeof(GLfloat), m_data.data());

    if (m_texCoords)
    {
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer(2, GL_FLOAT, stride * sizeof(GLfloat), m_data.data() + 3);
    }
    if (m_normals)
    {
        glEnableClientState(GL_NORMAL_ARRAY);
        glNormalPointer(GL_FLOAT, stride * sizeof(GLfloat), m_data.data() + (m_texCoords ? 5 : 3));
    }

    glDrawArrays(GL_TRIANGLES, 0, m_numVertices);

    glDisableClientState(GL_VERTEX_ARRAY);
    if (m_texCoords) { glDisableClientState(GL_TEXTURE_COORD_ARRAY); }
    if (m_normals)   { glDisableClientState(GL_NORMAL_ARRAY);        }

    glPopMatrix();
    glPopAttrib();
}

//-----------------------------------------------------------------------------

void WavefrontMesh::SetData(std::vector<float> && data, uint32_t numVertices, WavefrontMaterial::Ptr const& material, bool normals, bool texCoords)
{
    m_data = std::move(data);
    m_numVertices = numVertices;
    m_material = material;
    m_normals = normals;
    m_texCoords = texCoords;
}

//-----------------------------------------------------------------------------

WavefrontObject::WavefrontObject(std::string const& objFile) :
    m_file(objFile),
    m_options(WavefrontLoadOptions{ false })
{
    Read_OBJ();
}

//-----------------------------------------------------------------------------

WavefrontObject::WavefrontObject(std::string const & objFile, WavefrontLoadOptions const& options) :
    m_file(objFile),
    m_options(options)
{
    Read_OBJ();
}

//-----------------------------------------------------------------------------

void WavefrontObject::Draw()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPushMatrix();

    for (auto& mesh : m_meshes)
    {
        mesh->Draw();
    }

    glPopMatrix();
    glPopAttrib();
}

//-----------------------------------------------------------------------------

void WavefrontObject::Read_OBJ()
{
    std::vector<vec3> vertices;
    std::vector<vec3> normals;
    std::vector<vec3> textureCoordinates;

    std::ifstream stream(m_file, std::ios::in);
    if (!stream)
    {
        printf("Unable to read OBJ file '%s'.", m_file.c_str());
        return;
    }

    // Current mesh state
    WavefrontMesh::Ptr mesh = nullptr;
    WavefrontMaterial::Ptr material = nullptr;
    std::vector<float> buffer;
    uint32_t numVertices = 0;

    std::string identifier;
    std::string data;
    while (stream >> identifier)
    {
        if (identifier == "#")
        {
            stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        std::getline(stream, data);
        data = data.substr(1, std::string::npos);

        if (identifier == "mtllib")
        {
            Read_MTL(R"(Resources\)" + data);
        }
        else if (identifier == "v")
        {
            if (!m_options.BatchMeshes && mesh != nullptr)
            {
                mesh->SetData(std::move(buffer), numVertices, material, normals.size() != 0, textureCoordinates.size() != 0);
                m_meshes.push_back(mesh);

                // Clear out any left over state ready for the next mesh
                mesh = nullptr;
                material = nullptr;
                numVertices = 0;
                buffer.clear();
            }

            vec3 vertex;
            sscanf_s(data.c_str(), "%f %f %f", &vertex.x, &vertex.y, &vertex.z);
            vertices.push_back(vertex);
        }
        else if (identifier == "vn")
        {
            vec3 normal;
            sscanf_s(data.c_str(), "%f %f %f", &normal.x, &normal.y, &normal.z);
            normals.push_back(normal);
        }
        else if (identifier == "vt")
        {
            vec3 textureCoordinate;
            sscanf_s(data.c_str(), "%f %f %f", &textureCoordinate.x, &textureCoordinate.y, &textureCoordinate.z);
            textureCoordinates.push_back(textureCoordinate);
        }
        else if (identifier == "g")
        {
            mesh = std::make_shared<WavefrontMesh>(data);
        }
        else if (identifier == "usemtl")
        {
            auto it = m_materials.find(data);
            if (it != m_materials.end())
            {
                material = it->second;
            }
        }
        else if (identifier == "f")
        {
            auto faceDetails = Split(data, std::string(" "));

            for (auto& detail : faceDetails)
            {
                uint32_t iv = 0;
                uint32_t ivt = 0;
                uint32_t ivn = 0;

                if (textureCoordinates.size() != 0)
                {
                    sscanf_s(detail.c_str(), "%u/%u/%u", &iv, &ivt, &ivn);
                }
                else if (normals.size() != 0)
                {
                    sscanf_s(detail.c_str(), "%u//%u", &iv, &ivn);
                }
                else
                {
                    sscanf_s(detail.c_str(), "%u//", &iv);
                }

                if (iv != 0)
                {
                    vec3 v = vertices[iv - 1];
                    buffer.push_back(v.x);
                    buffer.push_back(v.y);
                    buffer.push_back(v.z);

                    ++numVertices;
                }
                if (ivt != 0)
                {
                    vec3 vt = textureCoordinates[ivt - 1];
                    buffer.push_back(vt.x);
                    buffer.push_back(vt.y);
                }
                if (ivn != 0)
                {
                    vec3 vn = normals[ivn - 1];
                    buffer.push_back(vn.x);
                    buffer.push_back(vn.y);
                    buffer.push_back(vn.z);
                }
            }
        }
    }

    stream.close();

    mesh->SetData(std::move(buffer), numVertices, material, normals.size() != 0, textureCoordinates.size() != 0);
    m_meshes.push_back(mesh);
}

//-----------------------------------------------------------------------------

void WavefrontObject::Read_MTL(std::string const& fileName)
{
    std::ifstream stream(fileName, std::ios::in);
    if (!stream)
    {
        printf("Unable to read MTL file '%s'.", fileName.c_str());
        return;
    }

    WavefrontMaterial::Ptr material = nullptr;

    std::string identifier;
    std::string data;
    while (stream >> identifier)
    {
        if (identifier == "#")
        {
            stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        std::getline(stream, data);
        data = data.substr(1, std::string::npos);

        if (identifier == "newmtl")
        {
            if (material != nullptr)
            {
                m_materials.insert(std::make_pair(material->Name, material));
            }
            material = std::make_shared<WavefrontMaterial>(data);
        }
        else if (identifier == "d")
        {
            sscanf_s(data.c_str(), "%f", &material->Transparency);
        }
        else if (identifier == "Ka")
        {
            sscanf_s(data.c_str(), "%f %f %f", &material->Ambient.x, &material->Ambient.y, &material->Ambient.z);
        }
        else if (identifier == "Kd")
        {
            sscanf_s(data.c_str(), "%f %f %f", &material->Diffuse.x, &material->Diffuse.y, &material->Diffuse.z);
        }
        else if (identifier == "Ks")
        {
            sscanf_s(data.c_str(), "%f %f %f", &material->Specular.x, &material->Specular.y, &material->Specular.z);
        }
        else if (identifier == "Ke")
        {
            sscanf_s(data.c_str(), "%f %f %f", &material->Emissive.x, &material->Emissive.y, &material->Emissive.z);
        }
    }

    m_materials.insert(std::make_pair(material->Name, material));
    stream.close();
}

//-----------------------------------------------------------------------------

} // namespace Framework
