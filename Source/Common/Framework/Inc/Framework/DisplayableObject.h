/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#pragma once

#include <memory>

#include <Framework/Vector.h>
#include <GL/freeglut.h>

namespace Framework
{

//-----------------------------------------------------------------------------

class DisplayableObject
{
public:
    typedef std::shared_ptr<DisplayableObject> Ptr;

    DisplayableObject();
    virtual ~DisplayableObject() {}

    virtual void Draw() = 0;
    virtual void Update(uint32_t frameTimeDelta) {}

    void SetPosition(vec3 const& position);
    void SetScale(float s);
    void SetScale(vec3 const& scale);
    void SetRotation(vec3 const& rotation);

    GLuint GetID() const;
    vec3 GetPosition() const;
    vec3 GetScale() const;
    vec3 GetRotation() const;

protected:
    vec3 m_position;
    vec3 m_scale;
    vec3 m_rotation;

private:
    static GLuint s_lastID;
    GLuint m_id;
};

//-----------------------------------------------------------------------------

class UserControlledDisplayableObject : public DisplayableObject
{
public:
    typedef std::shared_ptr<UserControlledDisplayableObject> Ptr;

    UserControlledDisplayableObject() {}
    virtual ~UserControlledDisplayableObject() {}

public: // Callbacks
    virtual void KeyAction(unsigned char key, bool keyDown, int x, int y) {}
    virtual void SpecialKeyAction(int key, bool keyDown, int x, int y) {}

    virtual void MouseAction(int button, bool mouseDown, int x, int y) {}
    virtual void MouseMotion(int x, int y) {}
    virtual void PassiveMouseMotion(int x, int y) {}
};

//-----------------------------------------------------------------------------

} // namespace Framework
