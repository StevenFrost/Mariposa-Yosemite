/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#include "MariposaYosemitePch.h"

#include "Aircraft.h"

#define _USE_MATH_DEFINES
#include <algorithm>
#include <GL/freeglut.h>
#include <math.h>

namespace Application
{

//-----------------------------------------------------------------------------

Aircraft::Aircraft() :
    AnimatedWavefrontObject(R"(Resources\piper-j3-cub.obj)", nullptr),
    m_actualState(std::make_shared<AircraftState>()),
    m_animationTime(0),
    m_startTime(0),
    m_turnAngle(0.0),
    m_bankAngle(0.0)
{
    m_animation.push_back(std::make_shared<AircraftState>(WaypointType::StraightAndLevel, dvec3(-560.0, 1.0, -74.0), dvec3(0.0, 82.55, 0.0), 0.0));
    m_animation.push_back(std::make_shared<AircraftState>(WaypointType::StraightAndLevel, dvec3(-353.3, 1.0, -44.1), dvec3(0.0, 82.55, 0.0), 30.9));
    m_animation.push_back(std::make_shared<AircraftState>(WaypointType::StraightAndLevel, dvec3(432.0, 149.1, 55.1), dvec3(0.0, 82.55, 0.0), 30.9));
    m_animation.push_back(std::make_shared<AircraftState>(WaypointType::StraightAndLevel, dvec3(935.1, 304.8, 121.7), dvec3(0.0, 82.55, 0.0), 50.0));
    m_animation.push_back(std::make_shared<AircraftState>(WaypointType::Turn, dvec3(1335.1, 304.8, 521.7), dvec3(0.0, 352.55, 0.0), dvec3(935.1, 304.8, 521.7), 45.0));
    m_animation.push_back(std::make_shared<AircraftState>(WaypointType::StraightAndLevel, dvec3(1335.1, 304.8, 600.0), dvec3(0.0, 352.55, 0.0), 50.0));
    m_animation.push_back(std::make_shared<AircraftState>(WaypointType::Turn, dvec3(935.1, 304.8, 1000.0), dvec3(0.0, 262.55, 0.0), dvec3(935.1, 304.8, 600.0), 45.0));
    m_animation.push_back(std::make_shared<AircraftState>(WaypointType::StraightAndLevel, dvec3(-1169.5, 304.8, 1000.0), dvec3(0.0, 262.55, 0.0), 50.0));

    m_actualState->Position = m_animation.front()->Position;

    // Generate timestamps for the animation
    auto it = m_animation.begin();
    while (++it != m_animation.end())
    {
        (*it)->TimeStamp = (*(it - 1))->TimeStamp + static_cast<uint32_t>((((*it)->Position - (*(it - 1))->Position).GetNorm() / ((*it)->Speed * 1.0)) * 1000.0);
    }
}

//-----------------------------------------------------------------------------

Aircraft::~Aircraft() {}

//-----------------------------------------------------------------------------

void Aircraft::Draw()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_CULL_FACE);
    glPushMatrix();
    {
        if (m_animation.front()->Type == WaypointType::Turn)
        {
            glTranslated(m_actualState->Position.x, m_actualState->Position.y, m_actualState->Position.z);
            glRotated(m_animation.back()->Orientation.y - m_turnAngle, 0.0, 1.0, 0.0);

            glTranslated(0.0, 1.5, 0.0);
            glRotated(m_bankAngle, 0.0, 0.0, 1.0);
            glTranslated(0.0, -1.5, 0.0);
        }
        else
        {
            glTranslated(m_actualState->Position.x, m_actualState->Position.y, m_actualState->Position.z);
            glRotated(m_actualState->Orientation.y, 0.0, 1.0, 0.0);
        }

        WavefrontObject::Draw();
    }
    glPopMatrix();
    glPopAttrib();
}

//-----------------------------------------------------------------------------

void Aircraft::Update(uint32_t frameTimeDelta)
{
    m_animationTime += frameTimeDelta;

    // Reset the animation if we hit the starting node
    if (m_animation.front()->TimeStamp == 0)
    {
        m_animationTime = 0;
        NextWaypoint();
    }

    // If we've passed the existing waypoint, look at the next one
    if (m_animation.front()->TimeStamp < (m_animationTime))
    {
        NextWaypoint();
    }

    auto previous = m_animation.back();
    auto next = m_animation.front();

    auto fraction = (m_animationTime - previous->TimeStamp) / static_cast<float>(next->TimeStamp - previous->TimeStamp);

    if (next->Type != WaypointType::Turn)
    {
        m_actualState->Position.x = previous->Position.x + (next->Position.x - previous->Position.x) * fraction;
        m_actualState->Position.y = previous->Position.y + (next->Position.y - previous->Position.y) * fraction;
        m_actualState->Position.z = previous->Position.z + (next->Position.z - previous->Position.z) * fraction;
    }
    else if (next->Type == WaypointType::Turn)
    {
        // Bank
        if (m_animationTime < previous->TimeStamp + 1500)
        {
            auto frac = (m_animationTime - previous->TimeStamp) / 1500.0;
            m_bankAngle = 20.0 * frac;
        }
        if (m_animationTime > next->TimeStamp - 1500)
        {
            auto frac = (next->TimeStamp - m_animationTime) / 1500.0;
            m_bankAngle = 20.0 * frac;
        }

        m_turnAngle = 90.0 * fraction;

        auto r = (next->Position - next->TurnCenter).GetNorm();
        auto n = atan2(m_animation.back()->Position.x - next->TurnCenter.x, m_animation.back()->Position.z - next->TurnCenter.z);

        m_actualState->Position.x = next->TurnCenter.x + (r * sin(((n * 180.0 / M_PI) - m_turnAngle) * (M_PI / 180.0)));
        m_actualState->Position.z = next->TurnCenter.z + (r * cos(((n * 180.0 / M_PI) - m_turnAngle) * (M_PI / 180.0)));
    }

    m_actualState->Orientation.y = next->Orientation.y;
}

//-----------------------------------------------------------------------------

void Aircraft::NextWaypoint()
{
    auto previous = m_animation.front();
    m_animation.pop_front();
    m_animation.push_back(previous);

    printf("Next Waypoint: %s\r\n", m_animation.front()->Position.ToString().c_str());

    if (previous->Type == WaypointType::Turn)
    {
        m_turnAngle = 0.0;
        m_bankAngle = 0.0;
    }
}

//-----------------------------------------------------------------------------

} // namespace Application
