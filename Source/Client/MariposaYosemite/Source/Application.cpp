/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#include "MariposaYosemitePch.h"

#include <memory>

#include <Framework/Context.h>

#include "AirportScene.h"
#include "Application.h"
#include "Terrain.h"

namespace Application
{

//-----------------------------------------------------------------------------

Application::Application(int argc, char *argv[]) :
    Context(argc, argv),
    m_environment(std::make_shared<Environment>()),
    m_perfCounter(std::make_shared<PerformanceCounter>())
{}

//-----------------------------------------------------------------------------

void Application::Idle()
{
    Context::Idle();

    ++m_perfCounter->Counter;
    if (m_currentFrameTime - m_perfCounter->StartTime > 1000)
    {
        m_perfCounter->FramesPerSecond = m_perfCounter->Counter;
        m_perfCounter->StartTime = m_currentFrameTime;
        m_perfCounter->Counter = 0;
    }
}

//-----------------------------------------------------------------------------

void Application::Draw()
{
    Context::Draw();

    char buf[128] = { '\0' };
    sprintf_s(buf, "Mariposa-Yosemite Airport Scene | G53GRA | FPS: %s (%s)",
        m_perfCounter->GetFPSString().data(), m_perfCounter->GetMSString().data()
    );
    glutSetWindowTitle(buf);
}

//-----------------------------------------------------------------------------

} // namespace Application

//-----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    auto context = std::make_shared<Application::Application>(argc, argv);
    auto scene = std::make_shared<Application::AirportScene>(context->GetEnvironment());

    context->SetScene(scene);
    context->Setup(1400, 700, "Mariposa-Yosemite Airport Scene | G53GRA");
    context->Run();

    return 0;
}

//-----------------------------------------------------------------------------
