/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#pragma once

#include <assert.h>
#include <memory>

#include <Framework/Context.h>

namespace Framework
{

//-----------------------------------------------------------------------------

class Callback
{
public:
    typedef std::shared_ptr<Callback> Ptr;

    static Callback::Ptr GetInstance();

    static void Idle();
    static void Draw();
    static void Reshape(int32_t width, int32_t height);

    static void KeyUp(unsigned char key, int x, int y);
    static void KeyDown(unsigned char key, int x, int y);

    static void SpecialKeyUp(int key, int x, int y);
    static void SpecialKeyDown(int key, int x, int y);

    static void MouseAction(int button, int state, int x, int y);
    static void MouseMotion(int x, int y);
    static void PassiveMouseMotion(int x, int y);

    template <class TLambda>
    static void CallbackHelper(TLambda && l)
    {
        auto instance = Callback::GetInstance();
        assert(instance->m_application != nullptr);

        l(instance->m_application);
    }

    void RegisterApplication(Context::Ptr const& application);

private:
    static Callback::Ptr s_instance;

    Context::Ptr m_application;
};

//-----------------------------------------------------------------------------

} // namespace Framework
