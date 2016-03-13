/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#include "FrameworkPch.h"

#include "Callback.h"

namespace Framework
{

//-----------------------------------------------------------------------------

Callback::Ptr Callback::s_instance = nullptr;

//-----------------------------------------------------------------------------

Callback::Ptr Callback::GetInstance()
{
    if (s_instance == nullptr)
    {
        s_instance = std::make_shared<Callback>();
    }
    return s_instance;
}

//-----------------------------------------------------------------------------

void Callback::Idle()
{
    CallbackHelper([](Context::Ptr const& application)
    {
        application->Idle();
    });
}

//-----------------------------------------------------------------------------

void Callback::Draw()
{
    CallbackHelper([](Context::Ptr const& application)
    {
        application->Draw();
    });
}

//-----------------------------------------------------------------------------

void Callback::Reshape(int32_t width, int32_t height)
{
    CallbackHelper([&](Context::Ptr const& application)
    {
        application->Reshape(width, height);
    });
}

//-----------------------------------------------------------------------------

void Callback::KeyUp(unsigned char key, int x, int y)
{
    CallbackHelper([&](Context::Ptr const& application)
    {
        application->KeyAction(key, false, x, y);
    });
}

//-----------------------------------------------------------------------------

void Callback::KeyDown(unsigned char key, int x, int y)
{
    CallbackHelper([&](Context::Ptr const& application)
    {
        application->KeyAction(key, true, x, y);
    });
}

//-----------------------------------------------------------------------------

void Callback::SpecialKeyUp(int key, int x, int y)
{
    CallbackHelper([&](Context::Ptr const& application)
    {
        application->SpecialKeyAction(key, false, x, y);
    });
}

//-----------------------------------------------------------------------------

void Callback::SpecialKeyDown(int key, int x, int y)
{
    CallbackHelper([&](Context::Ptr const& application)
    {
        application->SpecialKeyAction(key, true, x, y);
    });
}

//-----------------------------------------------------------------------------

void Callback::MouseAction(int button, int state, int x, int y)
{
    CallbackHelper([&](Context::Ptr const& application)
    {
        application->MouseAction(button, state == GLUT_DOWN, x, y);
    });
}

//-----------------------------------------------------------------------------

void Callback::MouseMotion(int x, int y)
{
    CallbackHelper([&](Context::Ptr const& application)
    {
        application->MouseMotion(x, y);
    });
}

//-----------------------------------------------------------------------------

void Callback::PassiveMouseMotion(int x, int y)
{
    CallbackHelper([&](Context::Ptr const& application)
    {
        application->PassiveMouseMotion(x, y);
    });
}

//-----------------------------------------------------------------------------

void Callback::RegisterApplication(Context::Ptr const& application)
{
    m_application = application;
}

//-----------------------------------------------------------------------------

} // namespace Framework
