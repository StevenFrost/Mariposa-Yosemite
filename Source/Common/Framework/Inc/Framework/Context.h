/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include <Framework/DisplayableObject.h>
#include <Framework/Scene.h>

namespace Framework
{

//-----------------------------------------------------------------------------

class Context : public std::enable_shared_from_this<Context>
{
public:
    typedef std::shared_ptr<Context> Ptr;

    Context(int argc, char *argv[]);
    virtual ~Context() {}

    virtual void Setup(int32_t width, int32_t height, std::string const& caption);
    virtual void Run();

    void SetScene(Scene::Ptr const& scene);

public: // Callbacks
    virtual void Idle();
    virtual void Draw();
    virtual void Reshape(int32_t width, int32_t height);

    virtual void KeyAction(unsigned char key, bool keyDown, int x, int y);
    virtual void SpecialKeyAction(int key, bool keyDown, int x, int y);

    virtual void MouseAction(int button, bool mouseDown, int x, int y);
    virtual void MouseMotion(int x, int y);
    virtual void PassiveMouseMotion(int x, int y);

private:
    void CheckGLError();

protected:
    int32_t     m_width;
    int32_t     m_height;
    std::string m_caption;

    int32_t m_currentFrameTime;
    int32_t m_previousFrameTime;

    Scene::Ptr m_scene;

private:
    uint32_t m_windowHandle;
};

//-----------------------------------------------------------------------------

} // namespace Framework
