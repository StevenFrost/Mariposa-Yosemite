/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#pragma once

#include <cstdint>
#include <memory>

namespace Framework
{

//-----------------------------------------------------------------------------

class Animation
{
public:
    typedef std::shared_ptr<Animation> Ptr;

    Animation() {}
    virtual ~Animation() {}

    virtual void Update(uint32_t frameTimeDelta) = 0;
};

//-----------------------------------------------------------------------------

} // namespace Framework
