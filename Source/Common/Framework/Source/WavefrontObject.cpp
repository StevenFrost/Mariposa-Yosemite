/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#include "FrameworkPch.h"

#include <Framework/WavefrontObject.h>

#include <fstream>

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

WavefrontObject::WavefrontObject(std::string const& objFile, TextureManager::Ptr const& textureManager) :
    m_file(objFile),
    m_textureManager(textureManager)
{
    ReadOBJ();
}

//-----------------------------------------------------------------------------

void WavefrontObject::Draw()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPushMatrix();

    //glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
    //glTranslatef(0.0f, 0.1f, 0.0f);
    glColor3f(0.608f, 0.608f, 0.608f);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glVertexPointer(3, GL_FLOAT, 6 * sizeof(GLfloat), m_data.data());
    glNormalPointer(GL_FLOAT, 6 * sizeof(GLfloat), m_data.data() + 3);

    glDrawArrays(GL_TRIANGLES, 0, m_data.size() / 2 / 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    glEnable(GL_DEPTH_TEST);

    glPopMatrix();
    glPopAttrib();
}

//-----------------------------------------------------------------------------

void WavefrontObject::ReadOBJ()
{
    std::vector<vec3> vertices;
    std::vector<vec3> normals;

    std::ifstream stream(m_file, std::ios::in);

    if (!stream)
    {
        printf("Unable to read OBJ file '%s'.", m_file.c_str());
        return;
    }

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
        if (identifier == "v")
        {
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
            float u, v;
            sscanf_s(data.c_str(), "%f %f", &u, &v);
        }
        else if (identifier == "f")
        {
            auto faceDetails = Split(data, std::string(" "));

            for (auto& detail : faceDetails)
            {
                uint32_t iv = 0;
                uint32_t ivn = 0;

                if (normals.size() != 0)
                {
                    sscanf_s(detail.c_str(), "%d//%d", &iv, &ivn);
                }
                else if (normals.size() == 0)
                {
                    sscanf_s(detail.c_str(), "%d//", &iv);
                }

                if (iv != 0)
                {
                    vec3 v = vertices[iv - 1];
                    m_data.push_back(v.x);
                    m_data.push_back(v.y);
                    m_data.push_back(v.z);
                }
                if (ivn != 0)
                {
                    vec3 vn = normals[ivn - 1];
                    m_data.push_back(vn.x);
                    m_data.push_back(vn.y);
                    m_data.push_back(vn.z);
                }
            }
        }
        else if (identifier == "mtl")
        {
            // PANIC!
        }
    }

    stream.close();
}

//-----------------------------------------------------------------------------

} // namespace Framework