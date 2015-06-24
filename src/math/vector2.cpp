
#include "xe/vector2.h"

#include <cmath>   // sqrt()

static XeVector2 _zero  (0, 0);
static XeVector2 _one   (1, 1);
static XeVector2 _unitx (1, 0);
static XeVector2 _unity (0, 1);

const XeVector2& XeVector2::Zero()
{
    return _zero;
}

const XeVector2& XeVector2::One()
{
    return _one;
}

const XeVector2& XeVector2::UnitX()
{
    return _unitx;
}

const XeVector2& XeVector2::UnitY()
{
    return _unity;
}

float XeVector2::Length(const XeVector2 &v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

float XeVector2::LengthSquared(const XeVector2 &v)
{
    return v.x * v.x + v.y * v.y;
}

float XeVector2::Dot(const XeVector2 &v1, const XeVector2 &v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

float XeVector2::Distance(const XeVector2 &v1, const XeVector2 &v2)
{
    return sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
}

float XeVector2::DistanceSquared(const XeVector2 &v1, const XeVector2 &v2)
{
    return (v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y);
}

float XeVector2::ManhattanDistance(const XeVector2 &v1, const XeVector2 &v2)
{
    return fabs(v1.x - v2.x) + fabs(v1.y - v2.y);
}

XeVector2 XeVector2::Normalize(const XeVector2 &v)
{
    return XeVector2::Multiply(v, 1.0f / v.length());
}

XeVector2 XeVector2::Reflect(const XeVector2 &v, const XeVector2 &n)
{
    float dot = XeVector2::Dot(v, n);

    XeVector2 r;
    r.x = v.x - (2.f * dot) * n.x;
    r.y = v.y - (2.f * dot) * n.y;
    return r;
}

bool XeVector2::Equal(const XeVector2 &v1, const XeVector2 &v2, float epsilon)
{
    return fabs(v1.x - v2.x) < epsilon && fabs(v1.y - v2.y) < epsilon;
}

bool XeVector2::NotEqual(const XeVector2 &v1, const XeVector2 &v2, float epsilon)
{
    return !XeVector2::Equal(v1, v2, epsilon);
}

XeVector2 XeVector2::Add(const XeVector2 &v1, const XeVector2 &v2)
{
    return XeVector2(v1.x + v2.x, v1.y + v2.y);
}

XeVector2 XeVector2::Subtract(const XeVector2 &v1, const XeVector2 &v2)
{
    return XeVector2(v1.x - v2.x, v1.y - v2.y);
}

XeVector2 XeVector2::Negate(const XeVector2 &v)
{
    return XeVector2(-v.x, -v.y);
}

XeVector2 XeVector2::Multiply(const XeVector2 &v, float amount)
{
    return XeVector2(amount * v.x, amount * v.y);
}

XeVector2 XeVector2::Divide(const XeVector2 &v, float amount)
{
    return XeVector2::Multiply(v, 1.0f / amount);
}

XeVector2 XeVector2::Lerp(const XeVector2 &v1, const XeVector2 &v2, float amount)
{
    return XeVector2((1.f - amount) * v1.x + amount * v2.x,
                     (1.f - amount) * v1.y + amount * v2.y);
}

XeVector2 XeVector2::Clamp(const XeVector2 &v, const XeVector2 &min, const XeVector2 &max)
{
    XeVector2 c = v;
    if (min.x > c.x) c.x = min.x;
    if (min.y > c.y) c.y = min.y;
    if (max.x < c.x) c.x = max.x;
    if (max.y < c.y) c.y = max.y;
    return c;
}

XeVector2 XeVector2::Min(const XeVector2 &v1, const XeVector2 &v2)
{
    XeVector2 c = v1;
    if (c.x > v2.x) c.x = v2.x;
    if (c.y > v2.y) c.y = v2.y;
    return c;
}

XeVector2 XeVector2::Max(const XeVector2 &v1, const XeVector2 &v2)
{
    XeVector2 c = v1;
    if (c.x < v2.x) c.x = v2.x;
    if (c.y < v2.y) c.y = v2.y;
    return c;
}

XeVector2 XeVector2::Transform(const XeMatrix &m, const XeVector2 &v)
{
    return XeVector2(v.x * m.m11 + v.y * m.m21 + m.m41,
                   v.x * m.m12 + v.y * m.m22 + m.m42);
}

XeVector2 XeVector2::TransformNormal(const XeMatrix &m, const XeVector2 &v)
{
    return XeVector2(v.x * m.m11 + v.y * m.m21,
                   v.x * m.m12 + v.y * m.m22);
}

XeVector2::XeVector2()
{
    x = y = 0;
}

XeVector2::XeVector2(float x, float y)
{
    this->x = x;
    this->y = y;
}

float XeVector2::length() const
{
    return XeVector2::Length(*this);
}

float XeVector2::lengthSquared() const
{
    return XeVector2::LengthSquared(*this);
}

float XeVector2::dot(const XeVector2 &other) const
{
    return XeVector2::Dot(*this, other);
}

float XeVector2::distanceTo(const XeVector2 &other) const
{
    return XeVector2::Distance(*this, other);
}

float XeVector2::distanceSquaredTo(const XeVector2 &other) const
{
    return XeVector2::DistanceSquared(*this, other);
}

float XeVector2::manhattanDistanceTo(const XeVector2 &other) const
{
    return XeVector2::ManhattanDistance(*this, other);
}

XeVector2 XeVector2::normalize() const
{
    return XeVector2::Normalize(*this);
}

XeVector2 XeVector2::reflect(const XeVector2 &n) const
{
    return XeVector2::Reflect(*this, n);
}

XeVector2 XeVector2::operator+ (const XeVector2& rhs) const
{
    return XeVector2::Add(*this, rhs);
}

XeVector2 XeVector2::operator- (const XeVector2& rhs) const
{
    return XeVector2::Subtract(*this, rhs);
}

XeVector2 XeVector2::operator- () const
{
    return XeVector2::Negate(*this);
}

XeVector2 XeVector2::operator* (float rhs) const
{
    return XeVector2::Multiply(*this, rhs);
}

XeVector2 XeVector2::operator/ (float rhs) const
{
    return XeVector2::Divide(*this, rhs);
}

XeVector2& XeVector2::operator+= (const XeVector2& rhs)
{
    x += rhs.x;
    y += rhs.y;

    return *this;
}

XeVector2& XeVector2::operator-= (const XeVector2& rhs)
{
    x -= rhs.x;
    y -= rhs.y;

    return *this;
}

XeVector2& XeVector2::operator*= (float rhs)
{
    x *= rhs;
    y *= rhs;

    return *this;
}

XeVector2& XeVector2::operator/= (float rhs)
{
    *this *= 1.f / rhs;
    return *this;
}

bool XeVector2::operator== (const XeVector2& rhs) const
{
    return XeVector2::Equal(*this, rhs);
}

bool XeVector2::operator!= (const XeVector2& rhs) const
{
    return XeVector2::NotEqual(*this, rhs);
}

XeVector2 XeVector2::clamp(const XeVector2 &min, const XeVector2 &max)
{
    return XeVector2::Clamp(*this, min, max);
}

XeVector2 XeVector2::transform(const XeMatrix &m)
{
    return XeVector2::Transform(m, *this);
}

XeVector2 XeVector2::transformNormal(const XeMatrix &m)
{
    return XeVector2::TransformNormal(m, *this);
}

XeVector2 operator* (float lhs, const XeVector2& rhs)
{
    return XeVector2::Multiply(rhs, lhs);
}
