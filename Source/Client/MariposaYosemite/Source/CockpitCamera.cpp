/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#include "MariposaYosemitePch.h"

#include "CockpitCamera.h"

namespace Application
{

//-----------------------------------------------------------------------------

CockpitCamera::CockpitCamera(Aircraft::Ptr const& aircraft) :
    m_aircraft(aircraft)
{}

//-----------------------------------------------------------------------------

void CockpitCamera::Update(uint32_t frameTimeDelta)
{
    m_eyePosition = m_aircraft->GetPosition() + dvec3(-0.25, 1.7, 0.0);
}

//-----------------------------------------------------------------------------

} // namespace Application
