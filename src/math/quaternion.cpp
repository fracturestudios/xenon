
#include "xe/quaternion.h"

#include <cmath> // sin, cos, sqrt

XeQuaternion __q_identity(0, 0, 0, 1);
XeQuaternion __q_zero(0, 0, 0, 0);

const XeQuaternion& XeQuaternion::Identity()
{
    return __q_identity;
}

const XeQuaternion& XeQuaternion::Zero()
{
    return __q_zero;
}

XeQuaternion XeQuaternion::FromAxisAngle(const XeVector3 &axis, float angle)
{
    XeQuaternion q;

    float halfAngle = .5 * angle;
    float cosHalf = cos(halfAngle);
    float sinHalf = sin(halfAngle);

    return XeQuaternion(axis.x * sinHalf, axis.y * sinHalf, axis.z * sinHalf, cosHalf);
}

XeQuaternion XeQuaternion::FromRotationXeMatrix(const XeMatrix &m)
{
    float n1 = (m.m11 + m.m22) + m.m33;

    if (n1 > 0.f)
    {
        float n2 = sqrt(n1 + 1.f);
        float n3 = .5f / n2;
        return XeQuaternion((m.m23 - m.m32) * n3,
                          (m.m31 - m.m13) * n3,
                          (m.m12 - m.m21) * n3,
                          n2 * .5f);
    }

    if ((m.m11 >= m.m22) && (m.m11 >= m.m33))
    {
        float n2 = sqrt(1.f + m.m11 - m.m22 - m.m33);
        float n3 = 0.5f / n2;
        return XeQuaternion(0.5f * n2,
                         (m.m12 + m.m21) * n3,
                         (m.m13 + m.m31) * n3,
                         (m.m23 - m.m32) * n3);
    }

    if (m.m22 > m.m33)
    {
        float n2 = sqrt(((1.f + m.m22) - m.m11) - m.m33);
        float n3 = 0.5f / n2;
        return XeQuaternion((m.m21 + m.m12) * n3,
                           0.5f * n2,
                          (m.m32 + m.m23) * n3,
                          (m.m31 - m.m13) * n3);
    }

    float n2 = sqrt(((1.f + m.m33) - m.m11) - m.m22);
    float n3 = 0.5f / n2;
    return XeQuaternion((m.m31 + m.m13) * n3,
                      (m.m32 + m.m23) * n3,
                      0.5f * n2,
                      (m.m12 - m.m21) * n3);
}

XeQuaternion XeQuaternion::FromYawPitchRoll(float yaw, float pitch, float roll)
{
    float halfYaw = yaw * .5f;
    float sinYaw = sin(halfYaw);
    float cosYaw = cos(halfYaw);
    float halfPitch = pitch * .5f;
    float sinPitch = sin(halfPitch);
    float cosPitch = cos(halfPitch);
    float halfRoll = roll * .5f;
    float sinRoll = sin(halfRoll);
    float cosRoll = cos(halfRoll);

    return XeQuaternion(((cosYaw * sinPitch) * cosRoll) + ((sinYaw * cosPitch) * sinRoll),
                      ((sinYaw * cosPitch) * cosRoll) - ((cosYaw * sinPitch) * sinRoll),
                      ((cosYaw * cosPitch) * sinRoll) - ((sinYaw * sinPitch) * cosRoll),
                      ((cosYaw * cosPitch) * cosRoll) + ((sinYaw * sinPitch) * sinRoll));
}

float XeQuaternion::Length(const XeQuaternion &q)
{
    return sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
}

float XeQuaternion::LengthSquared(const XeQuaternion &q)
{
    return q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
}

XeQuaternion XeQuaternion::Normalize(const XeQuaternion &q)
{
    float a = 1.f / XeQuaternion::Length(q);
    return XeQuaternion(q.x * a, q.y * a, q.z * a, q.w * a);
}

XeQuaternion XeQuaternion::Add(const XeQuaternion &q1, const XeQuaternion &q2)
{
    return XeQuaternion(q1.x + q2.x, q1.y + q2.y, q1.z + q2.z, q1.w + q2.w);
}

XeQuaternion XeQuaternion::Subtract(const XeQuaternion &q1, const XeQuaternion &q2)
{
    return XeQuaternion(q1.x - q2.x, q1.y - q2.y, q1.z - q2.z, q1.w - q2.w);
}

XeQuaternion XeQuaternion::Concatenate(const XeQuaternion &q1, const XeQuaternion &q2)
{
    return XeQuaternion::Multiply(q1, q2);
}

XeQuaternion XeQuaternion::Multiply(const XeQuaternion &q1, const XeQuaternion &q2)
{
    float t1 = (q1.y * q2.z) - (q1.z * q2.y);
    float t2 = (q1.z * q2.x) - (q1.x * q2.z);
    float t3 = (q1.x * q2.y) - (q1.y * q2.x);
    float t4 = ((q1.x * q2.x) + (q1.y * q2.y)) + (q1.z * q2.z);

    return XeQuaternion(((q1.x * q2.w) + (q2.x * q1.w)) + t1,
                      ((q1.y * q2.w) + (q2.y * q1.w)) + t2,
                      ((q1.z * q2.w) + (q2.z * q1.w)) + t3,
                      (q1.w * q2.w) - t4);
}

XeQuaternion XeQuaternion::Multiply(const XeQuaternion &q, float a)
{
    return XeQuaternion(q.x * a, q.y * a, q.z * a, q.w * a);
}

XeQuaternion XeQuaternion::Divide(const XeQuaternion &q1, const XeQuaternion &q2)
{
    float len = (((q2.x * q2.x) + (q2.y * q2.y)) + (q2.z * q2.z)) + (q2.w * q2.w);
    float oneOverLen = 1.f / len;
    float t1 = -q2.x * oneOverLen;
    float t2 = -q2.y * oneOverLen;
    float t3 = -q2.z * oneOverLen;
    float t4 = q2.w * oneOverLen;
    float t5 = (q1.y * t3) - (q1.z * t2);
    float t6 = (q1.z * t1) - (q1.x * t3);
    float t7 = (q1.x * t2) - (q1.y * t1);
    float t8 = ((q1.x * t1) + (q1.y * t2)) + (q1.z * t3);

    return XeQuaternion(((q1.x * t4) + (t1 * q1.w)) + t5,
                      ((q1.y * t4) + (t2 * q1.w)) + t6,
                      ((q1.z * t4) + (t3 * q1.w)) + t7,
                      (q1.w * t4) - t8);
}

XeQuaternion XeQuaternion::Divide(const XeQuaternion &q, float amount)
{
    return XeQuaternion::Multiply(q, 1.f / amount);
}

XeQuaternion XeQuaternion::Negate(const XeQuaternion &q)
{
    return XeQuaternion::Multiply(q, -1.f);
}

bool XeQuaternion::Equal(const XeQuaternion &q1, const XeQuaternion &q2, float epsilon)
{
    for (int i = 0; i < 4; i++)
        if (fabs(q1.xyzw[i] - q2.xyzw[i]) > epsilon)
            return false;
    return true;
}

bool XeQuaternion::NotEqual(const XeQuaternion &q1, const XeQuaternion &q2, float epsilon)
{
    for (int i = 0; i < 4; i++)
        if (fabs(q1.xyzw[i] - q2.xyzw[i]) > epsilon)
            return true;
    return false;
}

float XeQuaternion::Dot(const XeQuaternion &q1, const XeQuaternion &q2)
{
    return q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;
}

XeQuaternion XeQuaternion::Lerp(const XeQuaternion &q1, const XeQuaternion &q2, float amount)
{
    return XeQuaternion::Add(XeQuaternion::Multiply(q1, 1.f - amount), XeQuaternion::Multiply(q2, amount));
}

XeQuaternion XeQuaternion::Slerp(const XeQuaternion &q1, const XeQuaternion &q2, float amount)
{
    float a0 = amount;
    float len = (((q1.x * q2.x) + (q1.y * q2.y)) + (q1.z * q2.z)) + (q1.w * q2.w);
    float a, n1;

    bool negate = false;
    if (len < 0.f)
    {
        negate = true;
        len = -len;
    }

    if (len > 0.999999f)
    {
        n1 = 1.f - a0;
        a = negate ? -a0 : a0;
    }
    else
    {
        float n2 = acos(len);
        float n3 = 1.f / sin(n2);
        n1 = sin((1.f - a0) * n2) * n3;
        a = negate ? -sin(a0 * n2) * n3 : sin(a0 * n2) * n3;
    }

    return XeQuaternion(n1 * q1.x + a * q2.x,
                      n1 * q1.y + a * q2.y,
                      n1 * q1.z + a * q2.z,
                      n1 * q1.w + a * q2.w);
}

XeQuaternion XeQuaternion::Invert(const XeQuaternion &q)
{
    float f = -1.f / (q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
    return XeQuaternion(f * q.x, f * q.y, f * q.z, q.w);
}

XeQuaternion XeQuaternion::Conjugate(const XeQuaternion &q)
{
    return XeQuaternion(-q.x, -q.y, -q.z, q.w);
}

XeQuaternion::XeQuaternion()
{
    x = y = z = 0.f;
    w = 1.f;
}

XeQuaternion::XeQuaternion(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

float XeQuaternion::length() const
{
    return XeQuaternion::Length(*this);
}

float XeQuaternion::lengthSquared() const
{
    return XeQuaternion::LengthSquared(*this);
}

XeQuaternion XeQuaternion::normalize() const
{
    return XeQuaternion::Normalize(*this);
}

float XeQuaternion::dot(const XeQuaternion &other) const
{
    return XeQuaternion::Dot(*this, other);
}

XeQuaternion XeQuaternion::invert() const
{
    return XeQuaternion::Invert(*this);
}

XeQuaternion XeQuaternion::conjugate() const
{
    return XeQuaternion::Conjugate(*this);
}

bool XeQuaternion::operator== (const XeQuaternion& rhs) const
{
    return XeQuaternion::Equal(*this, rhs);
}

bool XeQuaternion::operator!= (const XeQuaternion& rhs) const
{
    return XeQuaternion::NotEqual(*this, rhs);
}

XeQuaternion XeQuaternion::operator+ (const XeQuaternion& rhs) const
{
    return XeQuaternion::Add(*this, rhs);
}

XeQuaternion XeQuaternion::operator- (const XeQuaternion& rhs) const
{
    return XeQuaternion::Subtract(*this, rhs);
}

XeQuaternion XeQuaternion::operator- () const
{
    return XeQuaternion::Negate(*this);
}

XeQuaternion XeQuaternion::operator* (const XeQuaternion& rhs) const
{
    return XeQuaternion::Multiply(*this, rhs);
}

XeQuaternion XeQuaternion::operator* (float rhs) const
{
    return XeQuaternion::Multiply(*this, rhs);
}

XeQuaternion XeQuaternion::operator/ (const XeQuaternion& rhs) const
{
    return XeQuaternion::Divide(*this, rhs);
}

XeQuaternion XeQuaternion::operator/ (float rhs) const
{
    return XeQuaternion::Divide(*this, rhs);
}

XeQuaternion& XeQuaternion::operator+= (const XeQuaternion& rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;

    return *this;
}

XeQuaternion& XeQuaternion::operator-= (const XeQuaternion& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    w -= rhs.w;

    return *this;
}

XeQuaternion& XeQuaternion::operator*= (const XeQuaternion& rhs)
{
    float t1 = (y * rhs.z) - (z * rhs.y);
    float t2 = (z * rhs.x) - (x * rhs.z);
    float t3 = (x * rhs.y) - (y * rhs.x);
    float t4 = ((x * rhs.x) + (y * rhs.y)) + (z * rhs.z);

    x = x * rhs.w + rhs.x * w + t1;
    y = y * rhs.w + rhs.y * w + t2;
    z = z * rhs.w + rhs.z * w + t3;
    w = w * rhs.w - t4;

    return *this;
}

XeQuaternion& XeQuaternion::operator*= (float a)
{
    x *= a;
    y *= a;
    z *= a;
    w *= a;

    return *this;
}

XeQuaternion& XeQuaternion::operator/= (const XeQuaternion& rhs)
{
    float len = (((rhs.x * rhs.x) + (rhs.y * rhs.y)) + (rhs.z * rhs.z)) + (rhs.w * rhs.w);
    float oneOverLen = 1.f / len;
    float t1 = -rhs.x * oneOverLen;
    float t2 = -rhs.y * oneOverLen;
    float t3 = -rhs.z * oneOverLen;
    float t4 = rhs.w * oneOverLen;
    float t5 = (y * t3) - (z * t2);
    float t6 = (z * t1) - (x * t3);
    float t7 = (x * t2) - (y * t1);
    float t8 = ((x * t1) + (y * t2)) + (z * t3);

    x = x * t4 + t1 * w + t5,
    y = y * t4 + t2 * w + t6,
    z = z * t4 + t3 * w + t7,
    w = w * t4 - t8;

    return *this;
}

XeQuaternion& XeQuaternion::operator/= (float a)
{
    *this *= 1.f / a;
    return *this;
}

XeQuaternion operator* (float lhs, const XeQuaternion& rhs)
{
    return XeQuaternion::Multiply(rhs, lhs);
}

XeQuaternion operator/ (float lhs, const XeQuaternion& rhs)
{
    return XeQuaternion::Divide(rhs, lhs);
}
