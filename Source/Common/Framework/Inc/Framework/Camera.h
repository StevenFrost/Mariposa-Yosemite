/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#pragma once

#include <cstdint>
#include <functional>
#include <memory>

#include <Framework/Vector.h>
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
    virtual void Projection(int32_t width, int32_t height);

    vec3 GetEyePosition() const;
    vec3 GetViewDirection() const;
    vec3 GetForwardVector() const;
    vec3 GetRightVector() const;
    vec3 GetUpVector() const;

    void SetEyePosition(vec3 position) { m_eyePosition = position; }

    std::function<void()> OnProjectionChanged;

public: // Callbacks
    virtual void KeyAction(unsigned char key, bool keyDown, int x, int y);
    virtual void SpecialKeyAction(int key, bool keyDown, int x, int y);

    virtual void MouseAction(int button, bool mouseDown, int x, int y);
    virtual void MouseMotion(int x, int y);
    virtual void PassiveMouseMotion(int x, int y);

protected:
    vec3 m_eyePosition;
    vec3 m_viewDirection;
    vec3 m_forward;
    vec3 m_right;
    vec3 m_up;

    bool m_keys[256] = { false };
    bool m_mouseDown;
    bool m_shiftDown;

    GLint m_mouseX;
    GLint m_mouseY;
};

//-----------------------------------------------------------------------------

} // namespace Framework
