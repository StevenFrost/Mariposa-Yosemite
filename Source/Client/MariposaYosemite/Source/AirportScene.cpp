/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#include "MariposaYosemitePch.h"

#include "AirportScene.h"

namespace Application
{

//-----------------------------------------------------------------------------

class Object : public Framework::DisplayableObject
{
public:
    virtual void Draw()
    {
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 10.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glutSolidCube(1.0f);
        glPopMatrix();
    }
};

//-----------------------------------------------------------------------------

void AirportScene::Initialise()
{
    m_objects.push_back(std::make_shared<Object>());
}

//-----------------------------------------------------------------------------

void AirportScene::KeyAction(unsigned char key, bool keyDown, int x, int y)
{
    Scene::KeyAction(key, keyDown, x, y);
}

//-----------------------------------------------------------------------------

} // namespace Application
