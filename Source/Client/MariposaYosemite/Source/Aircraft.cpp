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

template <class T>
T to_radians(T t)
{
    return t * (M_PI / 180.0);
}

template <class T>
T to_degrees(T t)
{
    return t * (180.0 / M_PI);
}

//-----------------------------------------------------------------------------

Aircraft::Aircraft() :
    WavefrontObject(R"(Resources\j3-body.obj)"),
    m_actualState(std::make_shared<AircraftState>()),
    m_animationTime(0),
    m_lightsEnabled(true),
    m_init(false),
    m_startTime(0),
    m_turnAngle(0.0),
    m_bankAngle(0.0),
    m_landingLight(std::make_shared<Framework::Light>(GL_LIGHT1, true)),
    m_leftNav(std::make_shared<Framework::Light>(GL_LIGHT2, true)),
    m_rightNav(std::make_shared<Framework::Light>(GL_LIGHT3, true)),
    m_leftStrobe(std::make_shared<Framework::StrobeLight>(GL_LIGHT4)),
    m_rightStrobe(std::make_shared<Framework::StrobeLight>(GL_LIGHT5))
{
    // Animation waypoint definitions                    |         Waypoint Type        |         Aircraft Position        |             Orientation          | Velocity | Timestamp |        Turn Center Point        | One Shot |
    m_animation.push_back(std::make_shared<AircraftState>(WaypointType::Stationary,       dvec3(-504.399, 0.0, -68.244),     dvec3(-11.31, 82.2725035191, 0.0), 0.0,       0,                                              true   ));
    m_animation.push_back(std::make_shared<AircraftState>(WaypointType::Stationary,       dvec3(-504.399, 0.0, -68.244),     dvec3(-11.31, 82.2725035191, 0.0), 0.0,       5000,                                           true   ));
    m_animation.push_back(std::make_shared<AircraftState>(WaypointType::RotationPoint,    dvec3(-192.407, 0.0, -26.198),     dvec3(0.0, 82.2725035191, 0.0),    30.9,                                                      true   ));
    m_animation.push_back(std::make_shared<AircraftState>(WaypointType::Climb,            dvec3(1496.626, 500.0, 203.773),   dvec3(0.0, 82.2725035191, 0.0),    30.9                                                              ));
    m_animation.push_back(std::make_shared<AircraftState>(WaypointType::StraightAndLevel, dvec3(1694.799, 500.0, 230.743),   dvec3(0.0, 82.2725035191, 0.0),    30.9                                                              ));
    m_animation.push_back(std::make_shared<AircraftState>(WaypointType::Turn,             dvec3(1951.604, 500.0, 568.459),   dvec3(0.0, 352.272503519, 0.0),    30.9,                  dvec3(1654.344, 500.0, 528.003)            ));
    m_animation.push_back(std::make_shared<AircraftState>(WaypointType::StraightAndLevel, dvec3(1924.634, 500.0, 766.632),   dvec3(0.0, 352.272503519, 0.0),    30.9                                                              ));
    m_animation.push_back(std::make_shared<AircraftState>(WaypointType::Turn,             dvec3(1586.919, 500.0, 1023.437),  dvec3(0.0, 262.272503519, 0.0),    30.9,                  dvec3(1627.374, 500.0, 726.177)            ));
    m_animation.push_back(std::make_shared<AircraftState>(WaypointType::StraightAndLevel, dvec3(-642.529, 500.0, 720.022),   dvec3(0.0, 262.272503519, 0.0),    30.9                                                              ));
    m_animation.push_back(std::make_shared<AircraftState>(WaypointType::Descent,          dvec3(-1633.395, 250.0, 585.171),  dvec3(0.0, 262.272503519, 0.0),    30.9                                                              ));
    m_animation.push_back(std::make_shared<AircraftState>(WaypointType::Turn,             dvec3(-1890.199, 250.0, 247.456),  dvec3(0.0, 172.272503519, 0.0),    30.9,                  dvec3(-1592.940, 250.0, 287.912)           ));
    m_animation.push_back(std::make_shared<AircraftState>(WaypointType::Descent,          dvec3(-1863.229, 200.0, 49.283),   dvec3(0.0, 172.272503519, 0.0),    30.9                                                              ));
    m_animation.push_back(std::make_shared<AircraftState>(WaypointType::Turn,             dvec3(-1525.514, 200.0, -207.521), dvec3(0.0, 82.2725035191, 0.0),    30.9,                  dvec3(-1565.969, 200.0, 89.738)            ));
    m_animation.push_back(std::make_shared<AircraftState>(WaypointType::Descent,          dvec3(-324.006, 0.0, -43.890),     dvec3(0.0, 82.2725035191, 0.0),    30.9                                                              ));
    m_animation.push_back(std::make_shared<AircraftState>(WaypointType::End,              dvec3(47.965, 0.0, 6.536),         dvec3(0.0, 82.2725035191, 0.0),    30.9                                                              ));

    InitAnimation();

    auto front = m_animation.front();
    m_animation.pop_front();
    m_animation.push_back(front);

    m_rudder       = std::make_shared<ControlSurface>(R"(Resources\j3-rudder.obj)", vec3(-0.012f, -2.1f, 4.724f));
    m_elevators    = std::make_shared<ControlSurface>(R"(Resources\j3-elevators.obj)", vec3(-0.012f, -1.749f, 4.669f));
    m_leftAileron  = std::make_shared<ControlSurface>(R"(Resources\j3-aileron-left.obj)", vec3(-0.012f, -1.922f, 1.2f));
    m_rightAileron = std::make_shared<ControlSurface>(R"(Resources\j3-aileron-right.obj)", vec3(-0.012f, -1.922f, 1.2f));

    m_prop = std::make_shared<Prop>();

    InitLights();
}

//-----------------------------------------------------------------------------

Aircraft::~Aircraft() {}

//-----------------------------------------------------------------------------

void Aircraft::Draw()
{
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
            glRotated(m_actualState->Orientation.y, 0.0, 1.0, 0.0); // Yaw

            // For pitch we need to consider the aircraft location. If we're on
            // the ground we pitch about the wheel axel otherwise we use the
            // aircraft's center of gravity.
            //if (m_animation.front()->Type == WaypointType::Climb || m_animation.front()->Type == WaypointType::Descent)
            //{
            //    glTranslated(0.0, 2.0, 0.0);
            //    glRotated(m_actualState->Orientation.x, 1.0, 0.0, 0.0);
            //    glTranslated(0.0, -2.0, 0.0);
            //}
            //else
            //{
                  glRotated(m_actualState->Orientation.x, 1.0, 0.0, 0.0);
            //}
        }

        // Lights
        m_landingLight->Draw();
        m_leftNav->Draw();
        m_rightNav->Draw();
        m_leftStrobe->Draw();
        m_rightStrobe->Draw();

        WavefrontObject::Draw();

        // Control Surfaces
        m_rudder->Draw();
        m_elevators->Draw();
        m_leftAileron->Draw();
        m_rightAileron->Draw();

        m_prop->Draw();
    }
    glPopMatrix();
    glEnable(GL_CULL_FACE);
}

//-----------------------------------------------------------------------------

void Aircraft::Update(uint32_t frameTimeDelta)
{
    m_animationTime += frameTimeDelta;

    UpdateAircraftState(frameTimeDelta);
    UpdateAttachedObjects(frameTimeDelta);
}

//-----------------------------------------------------------------------------

void Aircraft::SetLightsEnabled(bool enabled)
{
    m_lightsEnabled = enabled;

    m_landingLight->SetEnabled(enabled);
    m_leftNav->SetEnabled(enabled);
    m_rightNav->SetEnabled(enabled);
    m_leftStrobe->SetEnabled(enabled);
    m_rightStrobe->SetEnabled(enabled);
}

//-----------------------------------------------------------------------------

void Aircraft::InitLights()
{
    m_landingLight->SetAmbient(vec4(1.0f, 1.0f, 1.0f, 1.0f));
    m_landingLight->SetDiffuse(vec4(1.0f, 1.0f, 1.0f, 1.0f));
    m_landingLight->SetSpecular(vec4(1.0f, 1.0f, 1.0f, 1.0f));
    m_landingLight->SetDirection(vec3(0.0f, 0.0f, 1.0f));
    m_landingLight->SetPosition(vec3(0.0f, 1.0f, 1.5f));
    m_landingLight->SetAttenuationLinear(0.5f);
    m_landingLight->SetCutoff(80.0);
    m_landingLight->SetExponent(1.0f);

    m_leftNav->SetAmbient(vec4(0.7f, 0.0f, 0.0f, 1.0f));
    m_leftNav->SetDiffuse(vec4(1.0f, 0.0f, 0.0f, 1.0f));
    m_leftNav->SetSpecular(vec4(1.0f, 0.0f, 0.0f, 1.0f));
    m_leftNav->SetDirection(vec3(0.0f, -1.0f, 0.0f));
    m_leftNav->SetPosition(vec3(5.0f, 1.85f, 0.0f));
    m_leftNav->SetAttenuationLinear(2.0f);
    m_leftNav->SetCutoff(40.0);
    m_leftNav->SetExponent(6.0f);

    m_rightNav->SetAmbient(vec4(0.0f, 0.7f, 0.0f, 1.0f));
    m_rightNav->SetDiffuse(vec4(0.0f, 1.0f, 0.0f, 1.0f));
    m_rightNav->SetSpecular(vec4(0.0f, 1.0f, 0.0f, 1.0f));
    m_rightNav->SetDirection(vec3(0.0f, -1.0f, 0.0f));
    m_rightNav->SetPosition(vec3(-5.0f, 1.85f, 0.0f));
    m_rightNav->SetAttenuationLinear(2.0f);
    m_rightNav->SetCutoff(40.0);
    m_rightNav->SetExponent(6.0f);

    m_leftStrobe->SetAmbient(vec4(1.0f, 1.0f, 1.0f, 1.0f));
    m_leftStrobe->SetDiffuse(vec4(1.0f, 1.0f, 1.0f, 1.0f));
    m_leftStrobe->SetSpecular(vec4(1.0f, 1.0f, 1.0f, 1.0f));
    m_leftStrobe->SetDirection(vec3(0.0f, -1.0f, 0.0f));
    m_leftStrobe->SetPosition(vec3(5.0f, 1.7f, -1.3f));
    m_leftStrobe->SetAttenuationLinear(16.0f);
    m_leftStrobe->SetCutoff(180.0f);
    m_leftStrobe->SetExponent(6.0f);

    m_rightStrobe->SetAmbient(vec4(1.0f, 1.0f, 1.0f, 1.0f));
    m_rightStrobe->SetDiffuse(vec4(1.0f, 1.0f, 1.0f, 1.0f));
    m_rightStrobe->SetSpecular(vec4(1.0f, 1.0f, 1.0f, 1.0f));
    m_rightStrobe->SetDirection(vec3(0.0f, -1.0f, 0.0f));
    m_rightStrobe->SetPosition(vec3(-5.0f, 1.7f, -1.3f));
    m_rightStrobe->SetAttenuationLinear(16.0f);
    m_rightStrobe->SetCutoff(180.0f);
    m_rightStrobe->SetExponent(6.0f);
}

//-----------------------------------------------------------------------------

void Aircraft::InitAnimation()
{
    auto it = m_animation.begin();
    while (++it != m_animation.end())
    {
        auto previous = *(it - 1);
        auto next = *it;

        // Only generate timestamps that haven't been stated explicitly
        if (next->TimeStamp != std::numeric_limits<uint32_t>::max()) { continue; }

        double distanceBetweenWaypoints = 0.0;
        if (next->Type == WaypointType::Turn)
        {
            distanceBetweenWaypoints = (90.0 / 180.0) * M_PI * (next->Position - next->TurnCenter).GetNorm();
        }
        else
        {
            distanceBetweenWaypoints = (dvec3(next->Position.x, 0.0, next->Position.z) - dvec3(previous->Position.x, 0.0, previous->Position.z)).GetNorm();
        }

        double deltaTime = (distanceBetweenWaypoints * 2) / (previous->HorizontalSpeed + next->HorizontalSpeed);

        next->TimeStamp = previous->TimeStamp + static_cast<uint32_t>(deltaTime * 1000.0);
        next->Acceleration = (next->HorizontalSpeed - previous->HorizontalSpeed) / deltaTime;
        next->VerticalSpeed = (next->Position.y - previous->Position.y) / ((2 * ((deltaTime * 0.1) / 2)) + (deltaTime * 0.8));
    }
}

//-----------------------------------------------------------------------------

void Aircraft::NextWaypoint()
{
    if (m_animation.back()->OneShot)
    {
        m_animation.pop_back();
    }

    if (m_animation.back()->Type == WaypointType::End)
    {
        m_animationTime = 0;

        for (auto& state : m_animation)
        {
            state->TimeStamp = std::numeric_limits<uint32_t>::max();
        }
        m_animation.front()->TimeStamp = 0;

        InitAnimation();

        auto previous = m_animation.front();
        m_animation.pop_front();
        m_animation.push_back(previous);

        return;
    }

    auto previous = m_animation.front();
    m_animation.pop_front();
    m_animation.push_back(previous);

    if (previous->Type == WaypointType::Turn)
    {
        m_turnAngle = 0.0;
        m_bankAngle = 0.0;
    }

    m_actualState->Position = previous->Position;
    m_actualState->Acceleration = m_animation.front()->Acceleration;
    m_actualState->HorizontalSpeed = previous->HorizontalSpeed;
    m_actualState->Orientation = previous->Orientation;
    m_actualState->TurnCenter = m_animation.front()->TurnCenter;
    m_actualState->VerticalSpeed = 0.0;
}

//-----------------------------------------------------------------------------

template <class TLambda>
void linear_animation(uint32_t const& time, uint32_t const& base, uint32_t const& lower, uint32_t const& upper, TLambda && l)
{
    if ((time > (base + lower)) && (time < (base + upper)))
    {
        l((time - (base + lower)) / static_cast<double>(upper - lower));
    }
}

//-----------------------------------------------------------------------------

void Aircraft::UpdateAircraftState(uint32_t const& frameTimeDelta)
{
    if (!m_init)
    {
        m_animationTime = 0;
        m_actualState->Position = m_animation.front()->Position;
        m_actualState->HorizontalSpeed = m_animation.front()->HorizontalSpeed;
        m_actualState->VerticalSpeed = 0;

        m_init = true;
    }

    // If we've passed the current waypoint, start tracking the next one
    if (m_animation.front()->TimeStamp < m_animationTime)
    {
        printf("Expected Position: %s\tActual Position: %s\r\n", m_animation.front()->Position.ToString().c_str(), m_actualState->Position.ToString().c_str());
        NextWaypoint();
    }

    auto previous = m_animation.back();
    auto next = m_animation.front();

    // Yaw
    m_actualState->Orientation.y = next->Orientation.y;

    if (next->Type == WaypointType::Stationary)
    {
        m_actualState->Orientation.x = -11.31;
    }

    if (previous->Type == WaypointType::Stationary && next->Type == WaypointType::RotationPoint)
    { // Accelerating from stationary to rotation point
        linear_animation(m_animationTime, previous->TimeStamp, 8000, 10000, [&](double fraction)
        {
            m_actualState->Orientation.x = -11.31 * (1.0f - fraction);
        });
        linear_animation(m_animationTime, previous->TimeStamp, 7750, 8250, [&](double fraction)
        {
            m_elevators->SetRotation(vec3(static_cast<float>(-20.0f * fraction), 0.0f, 0.0f));
        });
        linear_animation(m_animationTime, previous->TimeStamp, 9500, 10000, [&](double fraction)
        {
            m_elevators->SetRotation(vec3(static_cast<float>(-20.0f * (1.0f - fraction)), 0.0f, 0.0f));
        });

        double accelerationComponent = next->Acceleration * (frameTimeDelta / 1000.0);
        m_actualState->HorizontalSpeed += accelerationComponent;

        m_actualState->Position.x += (m_actualState->HorizontalSpeed * sin(to_radians(next->Orientation.y))) * (frameTimeDelta / 1000.0);
        m_actualState->Position.z += (m_actualState->HorizontalSpeed * cos(to_radians(next->Orientation.y))) * (frameTimeDelta / 1000.0);
    }
    else if (next->Type == WaypointType::Climb || next->Type == WaypointType::Descent)
    { // Climbing out from the rotation point
        uint32_t deltaTime = next->TimeStamp - previous->TimeStamp;
        uint32_t verticalAccelerationTime = static_cast<uint32_t>(deltaTime * 0.1);
        double verticalAcceleration = next->VerticalSpeed / (verticalAccelerationTime / 1000.0);

        float pitch = (next->Type == WaypointType::Climb) ? -7.5f : 7.5f;
        float elevatorPitch = (next->Type == WaypointType::Climb) ? 12.0f : -12.0f;

        linear_animation(m_animationTime, previous->TimeStamp, 0, 1000, [&](double fraction)
        {
            m_actualState->Orientation.x = pitch * fraction;
        });
        linear_animation(m_animationTime, previous->TimeStamp, deltaTime - 2200, deltaTime, [&](double fraction)
        {
            m_actualState->Orientation.x = pitch * (1.0 - fraction);
        });

        linear_animation(m_animationTime, previous->TimeStamp, 0, 500, [&](double fraction)
        {
            m_elevators->SetRotation(vec3(static_cast<float>(elevatorPitch * fraction), 0.0f, 0.0f));
        });
        linear_animation(m_animationTime, previous->TimeStamp, deltaTime - 2400, deltaTime, [&](double fraction)
        {
            m_elevators->SetRotation(vec3(static_cast<float>(elevatorPitch * (1.0f - fraction)), 0.0f, 0.0f));
        });

        linear_animation(m_animationTime, previous->TimeStamp, 0, verticalAccelerationTime, [&](double fraction)
        {
            double accelerationComponent = verticalAcceleration * (frameTimeDelta / 1000.0);
            m_actualState->VerticalSpeed += accelerationComponent;
        });
        linear_animation(m_animationTime, previous->TimeStamp, deltaTime - verticalAccelerationTime, deltaTime, [&](double fraction)
        {
            double accelerationComponent = verticalAcceleration * (frameTimeDelta / 1000.0);
            m_actualState->VerticalSpeed -= accelerationComponent;
        });

        double accelerationComponent = next->Acceleration * (frameTimeDelta / 1000.0);
        m_actualState->HorizontalSpeed += accelerationComponent;

        m_actualState->Position.x += (m_actualState->HorizontalSpeed * sin(to_radians(next->Orientation.y))) * (frameTimeDelta / 1000.0);
        m_actualState->Position.y += m_actualState->VerticalSpeed * (frameTimeDelta / 1000.0);
        m_actualState->Position.z += (m_actualState->HorizontalSpeed * cos(to_radians(next->Orientation.y))) * (frameTimeDelta / 1000.0);
    }
    else if (next->Type == WaypointType::Turn)
    {
        uint32_t deltaTime = next->TimeStamp - previous->TimeStamp;

        linear_animation(m_animationTime, previous->TimeStamp, 0, 1500, [&](double fraction)
        {
            m_bankAngle = 20.0 * fraction;

            m_rudder->SetRotation(vec3(0.0f, static_cast<float>(m_bankAngle), 0.0f));
            m_elevators->SetRotation(vec3(static_cast<float>(m_bankAngle), 0.0f, 0.0f));
            m_leftAileron->SetRotation(vec3(-static_cast<float>(m_bankAngle), 0.0f, 0.0f));
            m_rightAileron->SetRotation(vec3(static_cast<float>(m_bankAngle), 0.0f, 0.0f));
        });
        linear_animation(m_animationTime, previous->TimeStamp, deltaTime - 1500, deltaTime, [&](double fraction)
        {
            m_bankAngle = 20.0 * (1.0 - fraction);

            m_rudder->SetRotation(vec3(0.0f, static_cast<float>(m_bankAngle), 0.0f));
            m_elevators->SetRotation(vec3(static_cast<float>(m_bankAngle), 0.0f, 0.0f));
            m_leftAileron->SetRotation(vec3(-static_cast<float>(m_bankAngle), 0.0f, 0.0f));
            m_rightAileron->SetRotation(vec3(static_cast<float>(m_bankAngle), 0.0f, 0.0f));
        });

        linear_animation(m_animationTime, previous->TimeStamp, 0, deltaTime, [&](double fraction)
        {
            m_turnAngle = 90.0 * fraction;

            double r = (previous->Position - next->TurnCenter).GetNorm();
            double n = atan2(previous->Position.x - next->TurnCenter.x, previous->Position.z - next->TurnCenter.z);

            m_actualState->Position.x = next->TurnCenter.x + (r * sin(n - to_radians(m_turnAngle)));
            m_actualState->Position.z = next->TurnCenter.z + (r * cos(n - to_radians(m_turnAngle)));
        });
    }
    else
    {
        double accelerationComponent = next->Acceleration * (frameTimeDelta / 1000.0);
        m_actualState->HorizontalSpeed += accelerationComponent;

        m_actualState->Position.x += (m_actualState->HorizontalSpeed * sin(to_radians(next->Orientation.y))) * (frameTimeDelta / 1000.0);
        m_actualState->Position.z += (m_actualState->HorizontalSpeed * cos(to_radians(next->Orientation.y))) * (frameTimeDelta / 1000.0);
    }
}

//-----------------------------------------------------------------------------

void Aircraft::UpdateAttachedObjects(uint32_t const& frameTimeDelta)
{
    if (m_lightsEnabled)
    {
        m_leftStrobe->Update(frameTimeDelta);
        m_rightStrobe->Update(frameTimeDelta);
    }
    m_prop->Update(frameTimeDelta);
}

//-----------------------------------------------------------------------------

} // namespace Application
