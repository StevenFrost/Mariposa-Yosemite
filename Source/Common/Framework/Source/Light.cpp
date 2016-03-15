/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#include "FrameworkPch.h"

#include <Framework/Light.h>

namespace Framework
{

//-----------------------------------------------------------------------------

#undef DRAW_DEBUG_LIGHT

//-----------------------------------------------------------------------------

Light::Light(GLenum light) :
    m_light(light),
    m_ambient(vec4(0.15f, 0.15f, 0.1f, 1.0f)),
    m_diffuse(vec4(0.8f, 0.8f, 0.8f, 1.0f)),
    m_specular(vec4(0.7f, 0.7f, 0.7f, 0.7f)),
    m_attenuationConstant(0.0f),
    m_attenuationLinear(0.005f),
    m_attenuationQuadratic(0.0f)
{}

//-----------------------------------------------------------------------------

void Light::Draw()
{
#ifdef DRAW_DEBUG_LIGHT
    glDisable(GL_LIGHTING);

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPushMatrix();

    glColor4f(m_diffuse.x, m_diffuse.y, m_diffuse.z, m_diffuse.w);

    glTranslatef(m_position.x, m_position.y, m_position.z);
    glutSolidSphere(10.0, 10, 10);

    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-m_position.x, -m_position.y, -m_position.z);
    glEnd();

    glPopMatrix();
    glPopAttrib();
#endif // DRAW_DEBUG_LIGHT

    glEnable(GL_LIGHTING);

    float buf[4] = { 0.0f };
    m_ambient.Data(buf);
    glLightfv(m_light, GL_AMBIENT, buf);

    m_diffuse.Data(buf);
    glLightfv(m_light, GL_DIFFUSE, buf);

    m_specular.Data(buf);
    glLightfv(m_light, GL_SPECULAR, buf);

    glLightf(m_light, GL_CONSTANT_ATTENUATION, m_attenuationConstant);
    glLightf(m_light, GL_LINEAR_ATTENUATION, m_attenuationLinear);
    glLightf(m_light, GL_QUADRATIC_ATTENUATION, m_attenuationQuadratic);

    float position[4] = { m_position.x, m_position.y, m_position.z, 1.0f };
    glLightfv(m_light, GL_POSITION, position);

    glEnable(m_light);
}

//-----------------------------------------------------------------------------

void Light::SetAmbient(vec4 const& ambient)
{
    m_ambient = ambient;
}

//-----------------------------------------------------------------------------

void Light::SetDiffuse(vec4 const& diffuse)
{
    m_diffuse = diffuse;
}

//-----------------------------------------------------------------------------

void Light::SetSpecular(vec4 const& specular)
{
    m_specular = specular;
}

//-----------------------------------------------------------------------------

void Light::SetAttenuationConstant(float constant)
{
    m_attenuationConstant = constant;
}

//-----------------------------------------------------------------------------

void Light::SetAttenuationLinear(float linear)
{
    m_attenuationLinear = linear;
}

//-----------------------------------------------------------------------------

void Light::SetAttenuationQuadratic(float quadratic)
{
    m_attenuationQuadratic = quadratic;
}

//-----------------------------------------------------------------------------

} // namespace Framework
