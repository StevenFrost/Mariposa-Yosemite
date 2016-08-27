/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#pragma once

#include <memory>
#include <string>

#include <Framework/DisplayableObject.h>

namespace Application
{

//-----------------------------------------------------------------------------

class Windsock : public Framework::DisplayableObject
{
public:
    typedef std::shared_ptr<Windsock> Ptr;

    Windsock();
    virtual ~Windsock() {}

    virtual void Draw();
};

//-----------------------------------------------------------------------------

} // namespace Application
