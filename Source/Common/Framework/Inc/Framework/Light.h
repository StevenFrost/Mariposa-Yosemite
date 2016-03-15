/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#pragma once

#include <Framework/DisplayableObject.h>
#include <Framework/Vector.h>
#include <GL/freeglut.h>

namespace Framework
{

//-----------------------------------------------------------------------------

class Light : public DisplayableObject
{
public:
    Light(GLenum light);
    virtual ~Light() {}

    virtual void Draw();

    void SetAmbient(vec4 const& ambient);
    void SetDiffuse(vec4 const& diffuse);
    void SetSpecular(vec4 const& specular);

    void SetAttenuationConstant(float constant);
    void SetAttenuationLinear(float linear);
    void SetAttenuationQuadratic(float quadratic);

protected:
    GLenum m_light;

    vec4 m_ambient;
    vec4 m_diffuse;
    vec4 m_specular;

    float m_attenuationConstant;
    float m_attenuationLinear;
    float m_attenuationQuadratic;
};

//-----------------------------------------------------------------------------

} // namespace Framework
