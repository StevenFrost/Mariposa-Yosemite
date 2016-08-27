/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#include "MariposaYosemitePch.h"

#include "Windsock.h"

#include <GL/freeglut.h>

namespace Application
{

//-----------------------------------------------------------------------------

Windsock::Windsock()
{
    m_rotation.x = -90.0f;
}

//-----------------------------------------------------------------------------

void Windsock::Draw()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPushMatrix();

    glDisable(GL_TEXTURE_2D);

    glTranslatef(m_position.x, m_position.y, m_position.z);
    glRotatef(m_rotation.x, 1.0f, 0.0f, 0.0f);
    glRotatef(m_rotation.y, 0.0f, 1.0f, 0.0f);
    glRotatef(m_rotation.z, 0.0f, 0.0f, 1.0f);

    glColor3f(0.7f, 0.7f, 0.7f);
    {
        glPushMatrix();
        glutSolidCylinder(0.2, 0.15, 16, 1);
        {
            glPushMatrix();
            glTranslatef(0.0f, 0.0f, 0.15f);
            glutSolidCylinder(0.05, 4.0, 16, 1);
            {
                glPushMatrix();
                glTranslatef(0.0f, 0.0f, 4.0f);
                glTranslatef(0.0f, 0.25f, 0.0f);
                glColor3f(1.0f, 0.5f, 0.0f);
                glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
                glutSolidCylinder(0.2, 0.4, 16, 1);
                {
                    glPushMatrix();
                    glTranslatef(0.0f, 0.0f, 0.4f);
                    glColor3f(1.0f, 1.0f, 1.0f);
                    glutSolidCylinder(0.2, 0.4, 16, 1);
                    {
                        glPushMatrix();
                        glTranslatef(0.0f, 0.0f, 0.4f);
                        glColor3f(1.0f, 0.5f, 0.0f);
                        glutSolidCylinder(0.2, 0.4, 16, 1);
                        {
                            glPushMatrix();
                            glTranslatef(0.0f, 0.0f, 0.4f);
                            glColor3f(1.0f, 1.0f, 1.0f);
                            glutSolidCylinder(0.2, 0.4, 16, 1);
                            {
                                glPushMatrix();
                                glTranslatef(0.0f, 0.0f, 0.4f);
                                glColor3f(1.0f, 0.5f, 0.0f);
                                glutSolidCylinder(0.2, 0.4, 16, 1);
                                glPopMatrix();
                            }
                            glPopMatrix();
                        }
                        glPopMatrix();
                    }
                    glPopMatrix();
                }
                glPopMatrix();
            }
            glPopMatrix();
        }
        glPopMatrix();
    }

    glPopMatrix();
    glPopAttrib();
}
//-----------------------------------------------------------------------------

} // namespace Application
