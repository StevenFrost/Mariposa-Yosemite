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
    typedef std::shared_ptr<Light> Ptr;

    Light(GLenum light, bool pointLight);
    virtual ~Light() {}

    virtual void Draw();

    void SetEnabled(bool enabled);
    void SetDirection(vec3 const& direction);

    void SetAmbient(vec4 const& ambient);
    void SetDiffuse(vec4 const& diffuse);
    void SetSpecular(vec4 const& specular);

    void SetAttenuationConstant(float constant);
    void SetAttenuationLinear(float linear);
    void SetAttenuationQuadratic(float quadratic);

    void SetExponent(float exponent);
    void SetCutoff(float cutoff);

protected:
    GLenum m_light;
    bool   m_pointLight;
    bool   m_enabled;

    vec3 m_direction;

    vec4 m_ambient;
    vec4 m_diffuse;
    vec4 m_specular;

    float m_attenuationConstant;
    float m_attenuationLinear;
    float m_attenuationQuadratic;

    float m_exponent;
    float m_cutoff;
};

//-----------------------------------------------------------------------------

class StrobeLight : public Light
{
public:
    typedef std::shared_ptr<StrobeLight> Ptr;

    StrobeLight(GLenum light);
    virtual ~StrobeLight() {}

    virtual void Update(uint32_t frameTimeDelta);

private:
    uint32_t m_animationTime;
    uint32_t m_strobeActiveTime;
    bool     m_strobeActive;

    const uint16_t m_enabledTime = 50U;
    const uint16_t m_disabledTime = 1000U;
};

//-----------------------------------------------------------------------------

} // namespace Framework
