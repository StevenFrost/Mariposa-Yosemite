/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#pragma once

#include <cmath>
#include <string>

namespace Framework
{

//-----------------------------------------------------------------------------

template <class T> struct Vector3;
template <class T> struct Vector4;

//-----------------------------------------------------------------------------

template <class T> Vector3<T> operator+(Vector3<T> const& u, Vector3<T> const& v);
template <class T> Vector3<T> operator-(Vector3<T> const& u, Vector3<T> const& v);
template <class T> Vector3<T> operator*(Vector3<T> const& u, T c);

template <class T> Vector4<T> operator+(Vector4<T> const& u, Vector4<T> const& v);
template <class T> Vector4<T> operator-(Vector4<T> const& u, Vector4<T> const& v);
template <class T> Vector4<T> operator*(Vector4<T> const& u, T c);

//-----------------------------------------------------------------------------

template <class T>
struct Vector3
{
    T x;
    T y;
    T z;

    Vector3() {}

    Vector3(T x, T y, T z) :
        x(x), y(y), z(z)
    {}

    template <class S>
    Vector3(Vector3<S> const& other) :
        x(static_cast<T>(other.x)),
        y(static_cast<T>(other.y)),
        z(static_cast<T>(other.z))
    {}

    void Normalize()
    {
        auto norm = GetNorm();
        x = x / norm;
        y = y / norm;
        z = z / norm;
    }

    Vector3 Cross(Vector3 const& rhs) const
    {
        return Vector3<T>((y * rhs.z) - (z * rhs.y), -((x * rhs.z) - (z * rhs.x)), (x * rhs.y) - (y * rhs.x));
    }

    T Dot(Vector3 const& rhs) const
    {
        return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);
    }

    T GetNorm() const
    {
        return sqrt((x * x) + (y * y) + (z * z));
    }

    void Data(T (&out)[3]) const
    {
        out[0] = x;
        out[1] = y;
        out[2] = z;
    }

    std::string ToString() const
    {
        char buf[128];
        sprintf_s(buf, "(%.4f, %.4f, %.4f)", x, y, z);
        return buf;
    }

    friend Vector3<T> operator+<>(Vector3<T> const& u, Vector3<T> const& v);
    friend Vector3<T> operator-<>(Vector3<T> const& u, Vector3<T> const& v);
    friend Vector3<T> operator*<>(Vector3<T> const& u, T c);
};

//-----------------------------------------------------------------------------

template <class T>
struct Vector4
{
    T x;
    T y;
    T z;
    T w;

    Vector4() {}

    Vector4(T x, T y, T z, T w) :
        x(x), y(y), z(z), w(w)
    {}

    template <class S>
    Vector4(Vector4<S> const& other) :
        x(static_cast<T>(other.x)),
        y(static_cast<T>(other.y)),
        z(static_cast<T>(other.z)),
        w(static_cast<T>(other.w))
    {}

    void Normalize()
    {
        auto norm = GetNorm();
        x = x / norm;
        y = y / norm;
        z = z / norm;
        w = w / norm;
    }

    T Dot(Vector4 const& rhs) const
    {
        return (x * rhs.x) + (y * rhs.y) + (z * rhs.z) + (w * rhs.w);
    }

    T GetNorm() const
    {
        return sqrt((x * x) + (y * y) + (z * z) + (w * w));
    }

    void Data(T (&out)[4]) const
    {
        out[0] = x;
        out[1] = y;
        out[2] = z;
        out[3] = w;
    }

    std::string ToString() const
    {
        char buf[128];
        sprintf_s(buf, "(%.4f, %.4f, %.4f, %.4f)", x, y, z, w);
        return buf;
    }

    friend Vector4<T> operator+<>(Vector4<T> const& u, Vector4<T> const& v);
    friend Vector4<T> operator-<>(Vector4<T> const& u, Vector4<T> const& v);
    friend Vector4<T> operator*<>(Vector4<T> const& u, T c);
};

//-----------------------------------------------------------------------------

template<> Vector3<float>::Vector3()
{
    x = 0.0f; y = 0.0f; z = 0.0f;
}

//-----------------------------------------------------------------------------

template<> Vector3<double>::Vector3()
{
    x = 0.0; y = 0.0; z = 0.0;
}

//-----------------------------------------------------------------------------

template <class T>
Vector3<T> operator+(Vector3<T> const& u, Vector3<T> const& v)
{
    return Vector3<T>(u.x + v.x, u.y + v.y, u.z + v.z);
}

//-----------------------------------------------------------------------------

template <class T>
Vector3<T> operator-(Vector3<T> const& u, Vector3<T> const& v)
{
    return Vector3<T>(u.x - v.x, u.y - v.y, u.z - v.z);
}

//-----------------------------------------------------------------------------

template <class T>
Vector3<T> operator*(Vector3<T> const& u, T c)
{
    return Vector3<T>(u.x * c, u.y * c, u.z * c);
}

//-----------------------------------------------------------------------------

template <> Vector4<float>::Vector4()
{
    x = 0.0f; y = 0.0f; z = 0.0f; w = 0.0f;
}

//-----------------------------------------------------------------------------

template <> Vector4<double>::Vector4()
{
    x = 0.0; y = 0.0; z = 0.0; w = 0.0;
}

//-----------------------------------------------------------------------------

template <class T>
Vector4<T> operator+(Vector4<T> const& u, Vector4<T> const& v)
{
    return Vector4<T>(u.x + v.x, u.y + v.y, u.z + v.z, u.w + v.w);
}

//-----------------------------------------------------------------------------

template <class T>
Vector4<T> operator-(Vector4<T> const& u, Vector4<T> const& v)
{
    return Vector4<T>(u.x - v.x, u.y - v.y, u.z - v.z, u.w - v.w);
}

//-----------------------------------------------------------------------------

template <class T>
Vector4<T> operator*(Vector4<T> const& u, T c)
{
    return Vector4<T>(u.x * c, u.y * c, u.z * c, u.w * c);
}

//-----------------------------------------------------------------------------

} // namespace Framework

//-----------------------------------------------------------------------------

typedef Framework::Vector3<float>  vec3;
typedef Framework::Vector3<double> dvec3;
typedef Framework::Vector4<float>  vec4;
typedef Framework::Vector4<double> dvec4;

//-----------------------------------------------------------------------------
