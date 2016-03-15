/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#pragma once

#include <memory>

#include <Framework/Context.h>

#include "Environment.h"
#include "PerformanceCounter.h"

namespace Application
{

//-----------------------------------------------------------------------------

class Application : public Framework::Context
{
public:
    typedef std::shared_ptr<Application> Ptr;

    Application(int argc, char *argv[]);
    virtual ~Application() {}

    virtual void Idle();
    virtual void Draw();

    Environment::Ptr GetEnvironment() const { return m_environment; }

private:
    Environment::Ptr        m_environment;
    PerformanceCounter::Ptr m_perfCounter;
};

//-----------------------------------------------------------------------------

} // namespace Application
