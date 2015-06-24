
#include "xe/vector3.h"

#include <cmath>   // sqrt()

static XeVector3 _zero  (0, 0, 0);
static XeVector3 _one   (1, 1, 1);
static XeVector3 _unitx (1, 0, 0);
static XeVector3 _unity (0, 1, 0);
static XeVector3 _unitz (0, 0, 1);

const XeVector3& XeVector3::Zero()
{
    return _zero;
}

const XeVector3& XeVector3::One()
{
    return _one;
}

const XeVector3& XeVector3::UnitX()
{
    return _unitx;
}

const XeVector3& XeVector3::UnitY()
{
    return _unity;
}

const XeVector3& XeVector3::UnitZ()
{
    return _unitz;
}

float XeVector3::Length(const XeVector3 &v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

float XeVector3::LengthSquared(const XeVector3 &v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

float XeVector3::Dot(const XeVector3 &v1, const XeVector3 &v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

XeVector3 XeVector3::Cross(const XeVector3 &v1, const XeVector3 &v2)
{
    XeVector3 v;
    v.x = (v1.y * v2.z) - (v1.z - v2.y);
    v.y = (v1.z - v2.x) - (v1.x - v2.z);
    v.z = (v1.x - v2.y) - (v1.y - v2.x);
    return v;
}

float XeVector3::Distance(const XeVector3 &v1, const XeVector3 &v2)
{
    return sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y) + (v1.z - v2.z) * (v1.z - v2.z));
}

float XeVector3::DistanceSquared(const XeVector3 &v1, const XeVector3 &v2)
{
    return (v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y) + (v1.z - v2.z) * (v1.z - v2.z);
}

float XeVector3::ManhattanDistance(const XeVector3 &v1, const XeVector3 &v2)
{
    return fabs(v1.x - v2.x) + fabs(v1.y - v2.y) + fabs(v1.z - v2.z);
}

XeVector3 XeVector3::Normalize(const XeVector3 &v)
{
    return XeVector3::Multiply(v, 1.0f / v.length());
}

XeVector3 XeVector3::Reflect(const XeVector3 &v, const XeVector3 &n)
{
    float dot = XeVector3::Dot(v, n);

    XeVector3 r;
    r.x = v.x - (2.f * dot) * n.x;
    r.y = v.y - (2.f * dot) * n.y;
    r.z = v.z - (2.f * dot) * n.z;

    return r;
}

bool XeVector3::Equal(const XeVector3 &v1, const XeVector3 &v2, float epsilon)
{
    return fabs(v1.x - v2.x) < epsilon && fabs(v1.y - v2.y) < epsilon && fabs(v1.z - v2.z) < epsilon;
}

bool XeVector3::NotEqual(const XeVector3 &v1, const XeVector3 &v2, float epsilon)
{
    return !XeVector3::Equal(v1, v2, epsilon);
}

XeVector3 XeVector3::Add(const XeVector3 &v1, const XeVector3 &v2)
{
    return XeVector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

XeVector3 XeVector3::Subtract(const XeVector3 &v1, const XeVector3 &v2)
{
    return XeVector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

XeVector3 XeVector3::Negate(const XeVector3 &v)
{
    return XeVector3(-v.x, -v.y, -v.z);
}

XeVector3 XeVector3::Multiply(const XeVector3 &v, float amount)
{
    return XeVector3(amount * v.x, amount * v.y, amount * v.z);
}

XeVector3 XeVector3::Divide(const XeVector3 &v, float amount)
{
    return XeVector3::Multiply(v, 1.0f / amount);
}

XeVector3 XeVector3::Lerp(const XeVector3 &v1, const XeVector3 &v2, float amount)
{
    XeVector3 v;
    v.x = (1.f - amount) * v1.x + amount * v2.x;
    v.y = (1.f - amount) * v1.y + amount * v2.y;
    v.z = (1.f - amount) * v1.z + amount * v2.z;

    return v;
}

XeVector3 XeVector3::Clamp(const XeVector3 &v, const XeVector3 &min, const XeVector3 &max)
{
    XeVector3 c = v;
    if (min.x > c.x) c.x = min.x;
    if (min.y > c.y) c.y = min.y;
    if (min.z > c.z) c.z = min.z;
    if (max.x < c.x) c.x = max.x;
    if (max.y < c.y) c.y = max.y;
    if (max.z < c.z) c.z = max.z;
    return c;
}

XeVector3 XeVector3::Min(const XeVector3 &v1, const XeVector3 &v2)
{
    XeVector3 c = v1;
    if (c.x > v2.x) c.x = v2.x;
    if (c.y > v2.y) c.y = v2.y;
    if (c.z > v2.z) c.z = v2.z;
    return c;
}

XeVector3 XeVector3::Max(const XeVector3 &v1, const XeVector3 &v2)
{
    XeVector3 c = v1;
    if (c.x < v2.x) c.x = v2.x;
    if (c.y < v2.y) c.y = v2.y;
    if (c.z < v2.z) c.z = v2.z;
    return c;
}

XeVector3 XeVector3::Transform(const XeMatrix &m, const XeVector3 &v)
{
    return XeVector3(v.x * m.m11 + v.y * m.m21 + v.z * m.m31 + m.m41,
                   v.x * m.m12 + v.y * m.m22 + v.z * m.m32 + m.m42,
                   v.x * m.m13 + v.y * m.m23 + v.z * m.m33 + m.m43);
}

XeVector3 XeVector3::TransformNormal(const XeMatrix &m, const XeVector3 &v)
{
    return XeVector3(v.x * m.m11 + v.y * m.m21 + v.z * m.m31,
                   v.x * m.m12 + v.y * m.m22 + v.z * m.m32,
                   v.x * m.m13 + v.y * m.m23 + v.z * m.m33);
}

XeVector3::XeVector3()
{
    x = y = z = 0;
}

XeVector3::XeVector3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

float XeVector3::length() const
{
    return XeVector3::Length(*this);
}

float XeVector3::lengthSquared() const
{
    return XeVector3::LengthSquared(*this);
}

float XeVector3::dot(const XeVector3 &other) const
{
    return XeVector3::Dot(*this, other);
}

XeVector3 XeVector3::cross(const XeVector3 &other) const
{
    return XeVector3::Cross(*this, other);
}

float XeVector3::distanceTo(const XeVector3 &other) const
{
    return XeVector3::Distance(*this, other);
}

float XeVector3::distanceSquaredTo(const XeVector3 &other) const
{
    return XeVector3::DistanceSquared(*this, other);
}

float XeVector3::manhattanDistanceTo(const XeVector3 &other) const
{
    return XeVector3::ManhattanDistance(*this, other);
}

XeVector3 XeVector3::normalize() const
{
    return XeVector3::Normalize(*this);
}

XeVector3 XeVector3::reflect(const XeVector3 &n) const
{
    return XeVector3::Reflect(*this, n);
}

XeVector3 XeVector3::operator+ (const XeVector3& rhs) const
{
    return XeVector3::Add(*this, rhs);
}

XeVector3 XeVector3::operator- (const XeVector3& rhs) const
{
    return XeVector3::Subtract(*this, rhs);
}

XeVector3 XeVector3::operator- () const
{
    return XeVector3::Negate(*this);
}

XeVector3 XeVector3::operator* (float rhs) const
{
    return XeVector3::Multiply(*this, rhs);
}

XeVector3 XeVector3::operator/ (float rhs) const
{
    return XeVector3::Divide(*this, rhs);
}

XeVector3& XeVector3::operator+= (const XeVector3& rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;

    return *this;
}

XeVector3& XeVector3::operator-= (const XeVector3& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;

    return *this;
}

XeVector3& XeVector3::operator*= (float rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;

    return *this;
}

XeVector3& XeVector3::operator/= (float rhs)
{
    *this *= 1.f / rhs;
    return *this;
}

bool XeVector3::operator== (const XeVector3& rhs) const
{
    return XeVector3::Equal(*this, rhs);
}

bool XeVector3::operator!= (const XeVector3& rhs) const
{
    return XeVector3::NotEqual(*this, rhs);
}

XeVector3 XeVector3::clamp(const XeVector3 &min, const XeVector3 &max)
{
    return XeVector3::Clamp(*this, min, max);
}

XeVector3 XeVector3::transform(const XeMatrix &m)
{
    return XeVector3::Transform(m, *this);
}

XeVector3 XeVector3::transformNormal(const XeMatrix &m)
{
    return XeVector3::TransformNormal(m, *this);
}

XeVector3 operator* (float lhs, const XeVector3& rhs)
{
    return XeVector3::Multiply(rhs, lhs);
}
