/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#include "MariposaYosemitePch.h"

#include <memory>

#include <Framework/Context.h>

#include "AirportScene.h"

//-----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    auto context = std::make_shared<Framework::Context>(argc, argv);
    auto scene = std::make_shared<Application::AirportScene>();

    context->SetScene(scene);
    context->Setup(1400, 700, "Mariposa-Yosemite Airport Scene - G53GRA");
    context->Run();

    return 0;
}

//-----------------------------------------------------------------------------
