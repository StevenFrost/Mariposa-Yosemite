/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#pragma once

#include <cstdint>
#include <memory>

#include <GL/freeglut.h>

namespace Framework
{

//-----------------------------------------------------------------------------

class Camera
{
public:
    typedef std::shared_ptr<Camera> Ptr;

    Camera();
    virtual ~Camera() {}

    virtual void Reset();
    virtual void Look();

    virtual void Update(uint32_t frameTimeDelta);

    void GetEyePosition(float &x, float &y, float &z) const;
    void GetViewDirection(float &x, float &y, float &z) const;
    void GetForwardVector(float &x, float &y, float &z) const;
    void GetRightVector(float &x, float &y, float &z) const;
    void GetUpVector(float &x, float &y, float &z) const;

public: // Callbacks
    virtual void KeyAction(unsigned char key, bool keyDown, int x, int y);
    virtual void SpecialKeyAction(int key, bool keyDown, int x, int y);

    virtual void MouseAction(int button, bool mouseDown, int x, int y);
    virtual void MouseMotion(int x, int y);
    virtual void PassiveMouseMotion(int x, int y);

protected:
    float m_eyePosition[3];
    float m_viewDirection[3];
    float m_forward[3];
    float m_right[3];
    float m_up[3];

    bool m_keys[256] = { false };
    bool m_mouseDown;

    GLint m_mouseX;
    GLint m_mouseY;
};

//-----------------------------------------------------------------------------

} // namespace Framework
