
#include "xe/vector4.h"

#include <cmath>   // sqrt()

static XeVector4 _zero  (0, 0, 0, 0);
static XeVector4 _one   (1, 1, 1, 1);
static XeVector4 _unitx (1, 0, 0, 0);
static XeVector4 _unity (0, 1, 0, 0);
static XeVector4 _unitz (0, 0, 1, 0);
static XeVector4 _unitw (0, 0, 0, 1);

const XeVector4& XeVector4::Zero()
{
    return _zero;
}

const XeVector4& XeVector4::One()
{
    return _one;
}

const XeVector4& XeVector4::UnitX()
{
    return _unitx;
}

const XeVector4& XeVector4::UnitY()
{
    return _unity;
}

const XeVector4& XeVector4::UnitZ()
{
    return _unitz;
}

const XeVector4& XeVector4::UnitW()
{
    return _unitw;
}

float XeVector4::Length(const XeVector4 &v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

float XeVector4::LengthSquared(const XeVector4 &v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
}

float XeVector4::Dot(const XeVector4 &v1, const XeVector4 &v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

XeVector4 XeVector4::Cross(const XeVector4 &v1, const XeVector4 &v2)
{
    XeVector4 v;
    v.x = (v1.y * v2.z) - (v1.z - v2.y);
    v.y = (v1.z - v2.x) - (v1.x - v2.z);
    v.z = (v1.x - v2.y) - (v1.y - v2.x);
    return v;
}

float XeVector4::Distance(const XeVector4 &v1, const XeVector4 &v2)
{
    return sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y) + (v1.z - v2.z) * (v1.z - v2.z) + (v1.w - v2.w) * (v1.w - v2.w));
}

float XeVector4::DistanceSquared(const XeVector4 &v1, const XeVector4 &v2)
{
    return (v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y) + (v1.z - v2.z) * (v1.z - v2.z) + (v1.w - v2.w) * (v1.w - v2.w);
}

float XeVector4::ManhattanDistance(const XeVector4 &v1, const XeVector4 &v2)
{
    return fabs(v1.x - v2.x) + fabs(v1.y - v2.y) + fabs(v1.z - v2.z) + fabs(v1.w - v2.w);
}

XeVector4 XeVector4::Normalize(const XeVector4 &v)
{
    return XeVector4::Multiply(v, 1.0f / v.length());
}

XeVector4 XeVector4::Reflect(const XeVector4 &v, const XeVector4 &n)
{
    float dot = XeVector4::Dot(v, n);

    XeVector4 r;
    r.x = v.x - 2.f * dot * n.x;
    r.y = v.y - 2.f * dot * n.y;
    r.z = v.z - 2.f * dot * n.z;
    r.w = v.w - 2.f * dot * n.w;

    return r;
}

bool XeVector4::Equal(const XeVector4 &v1, const XeVector4 &v2, float epsilon)
{
    return fabs(v1.x - v2.x) < epsilon && fabs(v1.y - v2.y) < epsilon && fabs(v1.z - v2.z) < epsilon;
}

bool XeVector4::NotEqual(const XeVector4 &v1, const XeVector4 &v2, float epsilon)
{
    return !XeVector4::Equal(v1, v2, epsilon);
}

XeVector4 XeVector4::Add(const XeVector4 &v1, const XeVector4 &v2)
{
    return XeVector4(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}

XeVector4 XeVector4::Subtract(const XeVector4 &v1, const XeVector4 &v2)
{
    return XeVector4(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
}

XeVector4 XeVector4::Negate(const XeVector4 &v)
{
    return XeVector4(-v.x, -v.y, -v.z, -v.w);
}

XeVector4 XeVector4::Multiply(const XeVector4 &v, float amount)
{
    return XeVector4(amount * v.x, amount * v.y, amount * v.z, amount * v.w);
}

XeVector4 XeVector4::Divide(const XeVector4 &v, float amount)
{
    return XeVector4::Multiply(v, 1.0f / amount);
}

XeVector4 XeVector4::Lerp(const XeVector4 &v1, const XeVector4 &v2, float amount)
{
    XeVector4 v;
    v.x = (1.f - amount) * v1.x + amount * v2.x;
    v.y = (1.f - amount) * v1.y + amount * v2.y;
    v.z = (1.f - amount) * v1.z + amount * v2.z;
    v.w = (1.f - amount) * v1.w + amount * v2.w;

    return v;
}

XeVector4 XeVector4::Clamp(const XeVector4 &v, const XeVector4 &min, const XeVector4 &max)
{
    XeVector4 c = v;
    if (min.x > c.x) c.x = min.x;
    if (min.y > c.y) c.y = min.y;
    if (min.z > c.z) c.z = min.z;
    if (min.w > c.w) c.w = min.w;
    if (max.x < c.x) c.x = max.x;
    if (max.y < c.y) c.y = max.y;
    if (max.z < c.z) c.z = max.z;
    if (max.w < c.w) c.w = max.w;
    return c;
}

XeVector4 XeVector4::Min(const XeVector4 &v1, const XeVector4 &v2)
{
    XeVector4 c = v1;
    if (c.x > v2.x) c.x = v2.x;
    if (c.y > v2.y) c.y = v2.y;
    if (c.z > v2.z) c.z = v2.z;
    if (c.w > v2.w) c.w = v2.w;
    return c;
}

XeVector4 XeVector4::Max(const XeVector4 &v1, const XeVector4 &v2)
{
    XeVector4 c = v1;
    if (c.x < v2.x) c.x = v2.x;
    if (c.y < v2.y) c.y = v2.y;
    if (c.z < v2.z) c.z = v2.z;
    if (c.w < v2.w) c.w = v2.w;
    return c;
}

XeVector4 XeVector4::Transform(const XeMatrix &m, const XeVector4 &v)
{
    return XeVector4(v.x * m.m11 + v.y * m.m21 + v.z * m.m31 + v.w * m.m41,
                   v.x * m.m12 + v.y * m.m22 + v.z * m.m32 + v.w * m.m42,
                   v.x * m.m13 + v.y * m.m23 + v.z * m.m33 + v.w * m.m43,
                   v.x * m.m14 + v.y * m.m24 + v.z * m.m34 + v.w * m.m44);
}

XeVector4::XeVector4()
{
    x = y = z = w = 0;
}

XeVector4::XeVector4(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

XeVector4::XeVector4(const XeVector3 &v3)
{
    x = v3.x;
    y = v3.y;
    z = v3.z;
    w = 1;
}

float XeVector4::length() const
{
    return XeVector4::Length(*this);
}

float XeVector4::lengthSquared() const
{
    return XeVector4::LengthSquared(*this);
}

float XeVector4::dot(const XeVector4 &other) const
{
    return XeVector4::Dot(*this, other);
}

XeVector4 XeVector4::cross(const XeVector4 &other) const
{
    return XeVector4::Cross(*this, other);
}

float XeVector4::distanceTo(const XeVector4 &other) const
{
    return XeVector4::Distance(*this, other);
}

float XeVector4::distanceSquaredTo(const XeVector4 &other) const
{
    return XeVector4::DistanceSquared(*this, other);
}

float XeVector4::manhattanDistanceTo(const XeVector4 &other) const
{
    return XeVector4::ManhattanDistance(*this, other);
}

XeVector4 XeVector4::normalize() const
{
    return XeVector4::Normalize(*this);
}

XeVector4 XeVector4::reflect(const XeVector4 &n) const
{
    return XeVector4::Reflect(*this, n);
}

XeVector4 XeVector4::operator+ (const XeVector4& rhs) const
{
    return XeVector4::Add(*this, rhs);
}

XeVector4 XeVector4::operator- (const XeVector4& rhs) const
{
    return XeVector4::Subtract(*this, rhs);
}

XeVector4 XeVector4::operator- () const
{
    return XeVector4::Negate(*this);
}

XeVector4 XeVector4::operator* (float rhs) const
{
    return XeVector4::Multiply(*this, rhs);
}

XeVector4 XeVector4::operator/ (float rhs) const
{
    return XeVector4::Divide(*this, rhs);
}

XeVector4& XeVector4::operator+= (const XeVector4& rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;

    return *this;
}

XeVector4& XeVector4::operator-= (const XeVector4& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    w -= rhs.w;

    return *this;
}

XeVector4& XeVector4::operator*= (float rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    w *= rhs;

    return *this;
}

XeVector4& XeVector4::operator/= (float rhs)
{
    *this *= 1.f / rhs;
    return *this;
}

bool XeVector4::operator== (const XeVector4& rhs) const
{
    return XeVector4::Equal(*this, rhs);
}

bool XeVector4::operator!= (const XeVector4& rhs) const
{
    return XeVector4::NotEqual(*this, rhs);
}

XeVector4 XeVector4::clamp(const XeVector4 &min, const XeVector4 &max)
{
    return XeVector4::Clamp(*this, min, max);
}

XeVector4 XeVector4::transform(const XeMatrix &m)
{
    return XeVector4::Transform(m, *this);
}

XeVector4 operator* (float lhs, const XeVector4& rhs)
{
    return XeVector4::Multiply(rhs, lhs);
}

