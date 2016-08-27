/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#pragma once

#include <cstdint>
#include <deque>
#include <memory>

#include <Framework/Camera.h>
#include <Framework/Light.h>
#include <Framework/WavefrontObject.h>

namespace Application
{

//-----------------------------------------------------------------------------

enum class WaypointType
{
    Stationary,
    RotationPoint,
    Climb,
    StraightAndLevel,
    Turn,
    Descent,
    LandingPoint,
    End
};

//-----------------------------------------------------------------------------

struct AircraftState
{
    typedef std::shared_ptr<AircraftState> Ptr;
    
    AircraftState() :
        Type(WaypointType::End),
        Position(0.0, 0.0, 0.0),
        Orientation(0.0, 0.0, 0.0),
        TurnCenter(0.0, 0.0, 0.0),
        VerticalSpeed(0.0),
        HorizontalSpeed(0.0),
        Acceleration(0.0),
        TimeStamp(0),
        OneShot(false)
    {}

    AircraftState(WaypointType type, dvec3 position, dvec3 orientation, double speed, bool oneShot = false) :
        Type(type),
        Position(position),
        Orientation(orientation),
        TurnCenter(0.0, 0.0, 0.0),
        VerticalSpeed(0.0),
        HorizontalSpeed(speed),
        Acceleration(0.0),
        TimeStamp(std::numeric_limits<uint32_t>::max()),
        OneShot(oneShot)
    {}

    AircraftState(WaypointType type, dvec3 position, dvec3 orientation, double speed, uint32_t timestamp, bool oneShot = false) :
        Type(type),
        Position(position),
        Orientation(orientation),
        TurnCenter(0.0, 0.0, 0.0),
        VerticalSpeed(0.0),
        HorizontalSpeed(speed),
        Acceleration(0.0),
        TimeStamp(timestamp),
        OneShot(oneShot)
    {}

    AircraftState(WaypointType type, dvec3 position, dvec3 orientation, double speed, dvec3 turnCenter, bool oneShot = false) :
        Type(type),
        Position(position),
        Orientation(orientation),
        TurnCenter(turnCenter),
        VerticalSpeed(0.0),
        HorizontalSpeed(speed),
        Acceleration(0.0),
        TimeStamp(std::numeric_limits<uint32_t>::max()),
        OneShot(oneShot)
    {}

    WaypointType Type;

    dvec3 Position;
    dvec3 Orientation;

    dvec3 TurnCenter;

    double   VerticalSpeed;   // m/s
    double   HorizontalSpeed; // m/s
    double   Acceleration;    // m/s^2
    uint32_t TimeStamp;       // ms

    bool OneShot;             // True if the state should only be encountered once
};

//-----------------------------------------------------------------------------

class Prop : public Framework::WavefrontObject
{
public:
    typedef std::shared_ptr<Prop> Ptr;

    Prop() :
        WavefrontObject(R"(Resources\j3-prop.obj)")
    {}
    virtual ~Prop() {}

    virtual void Draw()
    {
        glPushMatrix();
            glTranslatef(0.012f, 1.352f, -1.399f);
            glRotatef(m_rotation.z, 0.0f, 0.0f, 1.0f);
            glTranslatef(-0.012f, -1.352f, 1.399f);

            WavefrontObject::Draw();
        glPopMatrix();
    }
    virtual void Update(uint32_t frameTimeDelta)
    {
        m_rotation.z += 13000.0f * (frameTimeDelta / 1000.0f);
    }
};

//-----------------------------------------------------------------------------

class ControlSurface : public Framework::WavefrontObject
{
public:
    typedef std::shared_ptr<ControlSurface> Ptr;

    ControlSurface(std::string const& objFile, vec3 offset) :
        WavefrontObject(objFile),
        m_offset(offset)
    {}
    virtual ~ControlSurface() {}

    virtual void Draw()
    {
        glPushMatrix();
            glTranslatef(-m_offset.x, -m_offset.y, -m_offset.z);
            glRotatef(m_rotation.x, 1.0f, 0.0f, 0.0f);
            glRotatef(m_rotation.y, 0.0f, 1.0f, 0.0f);
            glRotatef(m_rotation.z, 0.0f, 0.0f, 1.0f);
            glTranslatef(m_offset.x, m_offset.y, m_offset.z);

            WavefrontObject::Draw();
        glPopMatrix();
    }

    virtual void Update(uint32_t frameTimeDelta) {}

private:
    vec3 m_offset;
};

//-----------------------------------------------------------------------------

class Aircraft : public Framework::WavefrontObject
{
public:
    typedef std::shared_ptr<Aircraft> Ptr;

    Aircraft();
    virtual ~Aircraft();

    virtual void Draw();
    virtual void Update(uint32_t frameTimeDelta);

    dvec3 GetPosition() const { return m_actualState->Position; }

    void SetLightsEnabled(bool enabled);
    bool GetLightsEnabled() const { return m_lightsEnabled; }

private:
    void InitLights();
    void InitAnimation();
    void NextWaypoint();

    void UpdateAircraftState(uint32_t const& frameTimeDelta);
    void UpdateAttachedObjects(uint32_t const& frameTimeDelta);

private:
    uint32_t m_animationTime;

    std::deque<AircraftState::Ptr> m_animation;
    uint32_t m_startTime;

    double m_turnAngle;
    double m_bankAngle;

    bool m_lightsEnabled;
    bool m_init;

    AircraftState::Ptr m_actualState;

    // Control surfaces
    ControlSurface::Ptr m_rudder;
    ControlSurface::Ptr m_elevators;
    ControlSurface::Ptr m_leftAileron;
    ControlSurface::Ptr m_rightAileron;

    Prop::Ptr m_prop;

    // Lights
    Framework::Light::Ptr       m_landingLight;
    Framework::Light::Ptr       m_leftNav;
    Framework::Light::Ptr       m_rightNav;
    Framework::StrobeLight::Ptr m_leftStrobe;
    Framework::StrobeLight::Ptr m_rightStrobe;
};

//-----------------------------------------------------------------------------

} // namespace Application
