/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

namespace Framework
{

//-----------------------------------------------------------------------------

inline void scale(float *a, float const& scale)
{
    for (int i = 0; i < 3; ++i, ++a)
    {
        (*a) = (*a) * scale;
    }
}

//-----------------------------------------------------------------------------

inline void add(float *a, const float *b, float const& scale = 1.0f)
{
    for (int i = 0; i < 3; ++i)
    {
        *a++ += scale * (*b++);
    }
}

//-----------------------------------------------------------------------------

inline void sub(float *a, const float *b, float const& scale = 1.0f)
{
    for (int i = 0; i < 3; ++i)
    {
        *a++ -= scale * (*b++);
    }
}

//-----------------------------------------------------------------------------

inline void norm(float *n)
{
    float l = 0.0f;
    for (int i = 0; i < 3; ++i)
    {
        l += n[i] * n[i];
    }

    l = sqrt(l);
    for (int i = 0; i < 3; ++i)
    {
        n[i] /= l;
    }
}

//-----------------------------------------------------------------------------

inline void cross(const float *a, const float *b, float *c)
{
    c[0] = (a[1] * b[2]) - (a[2] * b[1]);
    c[1] = (a[2] * b[0]) - (a[0] * b[2]);
    c[2] = (a[0] * b[1]) - (a[1] * b[0]);
}

//-----------------------------------------------------------------------------

inline void dot(const float *a, const float *b, float &dot)
{
    dot = (a[0] * b[0]) + (a[1] * b[1]) + (a[2] * b[2]);
}

//-----------------------------------------------------------------------------

} // namespace Framework
