/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#include "MariposaYosemitePch.h"

#include "TrackingCamera.h"

namespace Application
{

//-----------------------------------------------------------------------------

TrackingCamera::TrackingCamera(Aircraft::Ptr const& aircraft) :
    m_aircraft(aircraft)
{}

//-----------------------------------------------------------------------------

void TrackingCamera::Look()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    auto aircraftPosition = m_aircraft->GetPosition();
    gluLookAt(
        m_eyePosition.x, m_eyePosition.y, m_eyePosition.z,
        aircraftPosition.x, aircraftPosition.y, aircraftPosition.z,
        m_up.x, m_up.y, m_up.z
    );
}

//-----------------------------------------------------------------------------

} // namespace Application
