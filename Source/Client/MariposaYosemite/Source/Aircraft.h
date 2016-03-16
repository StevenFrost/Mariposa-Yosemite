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
    //dvec3 m_turnCenter;

    AircraftState::Ptr m_actualState;
};

//-----------------------------------------------------------------------------

} // namespace Application
