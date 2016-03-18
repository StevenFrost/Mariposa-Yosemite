/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#pragma once

#include <cstdint>
#include <deque>
#include <memory>

#include <Framework/Animation.h>
#include <Framework/AnimatedWavefrontObject.h>
#include <Framework/Camera.h>
#include <Framework/DisplayableObject.h>

namespace Application
{

//-----------------------------------------------------------------------------

enum class WaypointType
{
    StraightAndLevel,
    Turn
};

//-----------------------------------------------------------------------------

struct AircraftState
{
    typedef std::shared_ptr<AircraftState> Ptr;
    
    AircraftState() :
        Type(WaypointType::StraightAndLevel),
        Position(0.0, 0.0, 0.0),
        Orientation(0.0, 0.0, 0.0),
        TurnCenter(0.0, 0.0, 0.0),
        Speed(0.0),
        TimeStamp(0)
    {}

    AircraftState(WaypointType type, dvec3 position, dvec3 orientation, double speed) :
        Type(type),
        Position(position),
        Orientation(orientation),
        Speed(speed),
        TimeStamp(0)
    {}

    AircraftState(WaypointType type, dvec3 position, dvec3 orientation, dvec3 turnCenter, double speed) :
        Type(type),
        Position(position),
        Orientation(orientation),
        TurnCenter(turnCenter),
        Speed(speed),
        TimeStamp(0)
    {}

    WaypointType Type;

    dvec3 Position;
    dvec3 Orientation;

    dvec3 TurnCenter;

    double   Speed;     // m/s
    uint32_t TimeStamp; // ms
};

//-----------------------------------------------------------------------------

class Prop : public Framework::AnimatedWavefrontObject
{
public:
    typedef std::shared_ptr<Prop> Ptr;

    Prop() :
        AnimatedWavefrontObject(R"(Resources\j3-prop.obj)", nullptr)
    {}
    virtual ~Prop() {}

    virtual void Draw()
    {
        glPushMatrix();
            glTranslatef(0.012f, 1.352f, -1.399f);
            glRotatef(m_rotation.z, 0.0f, 0.0f, 1.0f);
            glTranslatef(-0.012f, -1.352f, 1.399f);

            AnimatedWavefrontObject::Draw();
        glPopMatrix();
    }
    virtual void Update(uint32_t frameTimeDelta)
    {
        m_rotation.z += 13000.0f * (frameTimeDelta / 1000.0f);
    }
};

//-----------------------------------------------------------------------------

class ControlSurface : public Framework::AnimatedWavefrontObject
{
public:
    typedef std::shared_ptr<ControlSurface> Ptr;

    ControlSurface(std::string const& objFile, vec3 offset) :
        AnimatedWavefrontObject(objFile, nullptr),
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

            AnimatedWavefrontObject::Draw();
        glPopMatrix();
    }

    virtual void Update(uint32_t frameTimeDelta) {}

private:
    vec3 m_offset;
};

//-----------------------------------------------------------------------------

class Aircraft : public Framework::AnimatedWavefrontObject
{
public:
    typedef std::shared_ptr<Aircraft> Ptr;

    Aircraft();
    virtual ~Aircraft();

    virtual void Draw();
    virtual void Update(uint32_t frameTimeDelta);

    dvec3 GetPosition() const { return m_actualState->Position; }

private:
    void NextWaypoint();

private:
    uint32_t m_animationTime;

    std::deque<AircraftState::Ptr> m_animation;
    uint32_t m_startTime;

    double m_turnAngle;
    double m_bankAngle;

    AircraftState::Ptr m_actualState;

    // Control surfaces
    ControlSurface::Ptr m_rudder;
    ControlSurface::Ptr m_elevators;
    ControlSurface::Ptr m_leftAileron;
    ControlSurface::Ptr m_rightAileron;

    Prop::Ptr m_prop;
};

//-----------------------------------------------------------------------------

} // namespace Application
