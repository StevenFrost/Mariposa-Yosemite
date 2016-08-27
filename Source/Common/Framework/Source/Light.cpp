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

Light::Light(GLenum light, bool pointLight) :
    m_light(light),
    m_pointLight(pointLight),
    m_enabled(true),
    m_direction(vec3(0.0f, -1.0f, 0.0f)),
    m_ambient(vec4(0.05f, 0.05f, 0.05f, 1.0f)),
    m_diffuse(vec4(0.5f, 0.5f, 0.5f, 1.0f)),
    m_specular(vec4(0.7f, 0.7f, 0.7f, 0.7f)),
    m_attenuationConstant(0.0f),
    m_attenuationLinear(0.005f),
    m_attenuationQuadratic(0.0f),
    m_exponent(0.0f),
    m_cutoff(180.0f)
{}

//-----------------------------------------------------------------------------

void Light::Draw()
{
    if (!m_enabled)
    {
        glDisable(m_light);
        return;
    }

#ifdef DRAW_DEBUG_LIGHT
    glDisable(GL_LIGHTING);
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPushMatrix();
        glColor3f(m_diffuse.x, m_diffuse.y, m_diffuse.z);

        glTranslatef(m_position.x, m_position.y, m_position.z);
        glScalef(m_scale.x, m_scale.y, m_scale.z);
        glutSolidSphere(0.1, 10, 10);

        glRotatef(m_rotation.x, 1.f, 0.f, 0.f);
        glRotatef(m_rotation.y, 0.f, 1.f, 0.f);
        glRotatef(m_rotation.z, 0.f, 0.f, 1.f);

        glLineWidth(2.0f);
        glBegin(GL_LINES);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(1.0f * m_direction.x, 1.0f * m_direction.y, 1.0f * m_direction.z);
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

    glLightf(m_light, GL_SPOT_EXPONENT, m_exponent);
    glLightf(m_light, GL_SPOT_CUTOFF, m_cutoff);

    glPushMatrix();
        float position[4] = { m_position.x, m_position.y, m_position.z, m_pointLight ? 1.0f : 0.0f };
        glLightfv(m_light, GL_POSITION, position);

        glRotatef(m_rotation.x, 1.0, 0.0, 0.0);
        glRotatef(m_rotation.y, 0.0, 1.0, 0.0);
        glRotatef(m_rotation.z, 0.0, 0.0, 1.0);

        float direction[3] = { m_direction.x, m_direction.y, m_direction.z };
        glLightfv(m_light, GL_SPOT_DIRECTION, direction);
    glPopMatrix();

    glEnable(m_light);
}

//-----------------------------------------------------------------------------

void Light::SetEnabled(bool enabled)
{
    m_enabled = enabled;
}

//-----------------------------------------------------------------------------

void Light::SetDirection(vec3 const& direction)
{
    m_direction = direction;
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

void Light::SetExponent(float exponent)
{
    m_exponent = exponent;
}

//-----------------------------------------------------------------------------

void Light::SetCutoff(float cutoff)
{
    m_cutoff = cutoff;
}

//-----------------------------------------------------------------------------

StrobeLight::StrobeLight(GLenum light) :
    Light(light, true)
{}

//-----------------------------------------------------------------------------

void StrobeLight::Update(uint32_t frameTimeDelta)
{
    m_animationTime += frameTimeDelta;

    if (m_animationTime - m_strobeActiveTime > (m_strobeActive ? m_enabledTime : m_disabledTime))
    {
        m_strobeActiveTime = m_animationTime;
        m_strobeActive = !m_strobeActive;

        SetEnabled(m_strobeActive);
    }
}

//-----------------------------------------------------------------------------

} // namespace Framework
