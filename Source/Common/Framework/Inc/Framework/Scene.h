/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include <Framework/Camera.h>
#include <Framework/DisplayableObject.h>

namespace Framework
{

//-----------------------------------------------------------------------------

class Scene
{
public:
    typedef std::shared_ptr<Scene> Ptr;

    Scene();
    virtual ~Scene() {}

    virtual void Initialise();

    virtual void Draw();
    virtual void Update(uint32_t frameTimeDelta);

public: // Callbacks
    virtual void Reshape(int32_t width, int32_t height);

    virtual void KeyAction(unsigned char key, bool keyDown, int x, int y);
    virtual void SpecialKeyAction(int key, bool keyDown, int x, int y);

    virtual void MouseAction(int button, bool mouseDown, int x, int y);
    virtual void MouseMotion(int x, int y);
    virtual void PassiveMouseMotion(int x, int y);

protected:
    std::vector<DisplayableObject::Ptr> m_objects;

    Camera::Ptr m_camera;

    int32_t m_width;
    int32_t m_height;
};

//-----------------------------------------------------------------------------

} // namespace Framework
