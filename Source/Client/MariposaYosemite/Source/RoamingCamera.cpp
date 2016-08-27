/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#include "MariposaYosemitePch.h"

#include "RoamingCamera.h"

namespace Application
{

//-----------------------------------------------------------------------------

void RoamingCamera::Look()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    if (m_eyePosition.y < 0.2f)
    {
        m_eyePosition.y = 0.2f;
    }

    gluLookAt(
        m_eyePosition.x, m_eyePosition.y, m_eyePosition.z,
        m_eyePosition.x + m_viewDirection.x, m_eyePosition.y + m_viewDirection.y, m_eyePosition.z + m_viewDirection.z,
        m_up.x, m_up.y, m_up.z
    );
}

//-----------------------------------------------------------------------------

} // namespace Application
