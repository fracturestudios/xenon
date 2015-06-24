
#include "xe/matrix.h"

#include "xe/vector2.h"
#include "xe/vector3.h"
#include "xe/vector4.h"
#include "xe/quaternion.h"

#include <cmath>    // sin(), cos()

XeMatrix __m_identity (1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
XeMatrix __m_zero     (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

const XeMatrix& XeMatrix::Identity()
{
    return __m_identity;
}

const XeMatrix& XeMatrix::Zero()
{
    return __m_zero;
}

XeVector3 XeMatrix::Up(const XeMatrix &m)
{
    return XeVector3(m.m21, m.m22, m.m23);
}

XeVector3 XeMatrix::Down(const XeMatrix &m)
{
    return XeVector3(-m.m21, -m.m22, -m.m23);
}

XeVector3 XeMatrix::Left(const XeMatrix &m)
{
    return XeVector3(-m.m11, -m.m12, -m.m13);
}

XeVector3 XeMatrix::Right(const XeMatrix &m)
{
    return XeVector3(m.m11, m.m12, m.m13);
}

XeVector3 XeMatrix::Forward(const XeMatrix &m)
{
    return XeVector3(-m.m31, -m.m32, -m.m33);
}

XeVector3 XeMatrix::Backward(const XeMatrix &m)
{
    return XeVector3(m.m31, m.m32, m.m33);
}

XeVector3 XeMatrix::Translation(const XeMatrix &m)
{
    return XeVector3(m.m41, m.m42, m.m43);
}

XeMatrix XeMatrix::Billboard(const XeVector3 &objectPos, const XeVector3 &cameraPos, const XeVector3 &up)
{
    XeVector3 z = (objectPos - cameraPos).normalize();
    XeVector3 x = XeVector3::Cross(up, z);
    XeVector3 y = XeVector3::Cross(z, x);

    return XeMatrix(x.x, x.y, x.z, 0,
                  y.x, y.y, y.z, 0,
                  z.x, z.y, z.z, 0,
                  objectPos.x, objectPos.y, objectPos.z, 1);
}

XeMatrix XeMatrix::FromAxisAngle(const XeVector3 &axis, float angle)
{
    float x = axis.x;
    float y = axis.y;
    float z = axis.z;
    float sinTheta = sin(angle);
    float cosTheta = cos(angle);
    float xx = x * x;
    float yy = y * y;
    float zz = z * z;
    float xy = x * y;
    float xz = x * z;
    float yz = y * z;

    XeMatrix m;
    m.m11 = xx + (cosTheta * (1.f - xx));
    m.m12 = (xy - (cosTheta * xy)) + (sinTheta * z);
    m.m13 = (xz - (cosTheta * xz)) - (sinTheta * y);
    m.m21 = (xy - (cosTheta * xy)) - (sinTheta * z);
    m.m22 = yy + (cosTheta * (1.f - yy));
    m.m23 = (yz - (cosTheta * yz)) + (sinTheta * x);
    m.m31 = (xz - (cosTheta * xz)) + (sinTheta * y);
    m.m32 = (yz - (cosTheta * yz)) - (sinTheta * x);
    m.m33 = zz + (cosTheta * (1.f - zz));

    return m;
}

XeMatrix XeMatrix::FromXeQuaternion(const XeQuaternion &q)
{
    float xx = q.x * q.x;
    float yy = q.y * q.y;
    float zz = q.z * q.z;
    float xy = q.x * q.y;
    float zw = q.z * q.w;
    float zx = q.z * q.x;
    float yw = q.y * q.w;
    float yz = q.y * q.z;
    float xw = q.x * q.w;

    return XeMatrix(1.f - (2.f * (yy + zz)), 2.f * (xy + zw),         2.f * (zx - yw),         0,
                  2.f * (xy - zw),         1.f - (2.f * (zz + xx)), 2.f * (yz + xw),         0,
                  2.f * (zx + yw),         2.f * (yz - xw),         1.f - (2.f * (yy + xx)), 0,
                  0,                       0,                       0,                       1);
}

XeMatrix XeMatrix::FromYawPitchRoll(float yaw, float pitch, float roll)
{
    return XeMatrix::FromXeQuaternion(XeQuaternion::FromYawPitchRoll(yaw, pitch, roll));
}

XeMatrix XeMatrix::LookAt(const XeVector3 &cameraPos, const XeVector3 &targetPos, const XeVector3 &up)
{
    XeVector3 z = (cameraPos - targetPos).normalize();
    XeVector3 x = XeVector3::Cross(up, z).normalize();
    XeVector3 y = XeVector3::Cross(z, x);

    return XeMatrix(x.x, y.x, z.x, 0.f,
                  x.y, y.y, z.y, 0.f,
                  x.z, y.z, z.z, 0.f,
                  -x.dot(cameraPos), -y.dot(cameraPos), -z.dot(cameraPos), 1.f);
}

XeMatrix XeMatrix::Orthographic(float width, float height, float znear, float zfar)
{
    return XeMatrix(2.f / width, 0,            0,                      0,
                  0,           2.f / height, 0,                      0,
                  0,           0,            1.f / (znear - zfar),   0,
                  0,           0,            znear / (znear - zfar), 1);
}

XeMatrix XeMatrix::Perspective(float width, float height, float znear, float zfar)
{
    return XeMatrix(2.f * znear / width, 0,                    0,                                0,
                  0,                   2.f * znear / height, 0,                                0,
                  0,                   0,                    zfar / (znear - zfar),           -1,
                  0,                   0,                    (znear * zfar) / (znear - zfar),  0);
}

XeMatrix XeMatrix::PerspectiveFieldOfView(float fieldOfView, float aspectRatio, float znear, float zfar)
{
    float width = 1.f / tan(.5f * fieldOfView);
    float height = width / aspectRatio;

    return XeMatrix(height, 0,     0,                                0,
                  0,      width, 0,                                0,
                  0,      0,     zfar / (znear - zfar),           -1,
                  0,      0,     (znear * zfar) / (znear - zfar),  0);
}

XeMatrix XeMatrix::Scale(float a)
{
    return XeMatrix(a, 0, 0, 0,
                  0, a, 0, 0,
                  0, 0, a, 0,
                  0, 0, 0, 1);
}

XeMatrix XeMatrix::Scale(const XeVector3 &a)
{
    return XeMatrix(a.x, 0,   0,   0,
                  0,   a.y, 0,   0,
                  0,   0,   a.z, 0,
                  0,   0,   0,   1);
}

XeMatrix XeMatrix::Scale(float x, float y, float z)
{
    return XeMatrix(x, 0, 0, 0,
                  0, y, 0, 0,
                  0, 0, z, 0,
                  0, 0, 0, 1);
}

XeMatrix XeMatrix::RotateX(float angle)
{
    float sinTheta = sin(angle);
    float cosTheta = cos(angle);

    return XeMatrix(1,         0,        0, 0,
                  0,  cosTheta, sinTheta, 0,
                  0, -sinTheta, cosTheta, 0,
                  0,         0,        0, 1);
}

XeMatrix XeMatrix::RotateY(float angle)
{
    float sinTheta = sin(angle);
    float cosTheta = cos(angle);

    return XeMatrix(cosTheta, 0, -sinTheta, 0,
                  0,        1,         0, 0,
                  sinTheta, 0,  cosTheta, 0,
                  0,        0,         0, 1);
}

XeMatrix XeMatrix::RotateZ(float angle)
{
    float sinTheta = sin(angle);
    float cosTheta = cos(angle);

    return XeMatrix(cosTheta,  sinTheta, 0, 0,
                  -sinTheta, cosTheta, 0, 0,
                  0,         0,        1, 0,
                  0,         0,        0, 1);
}

XeMatrix XeMatrix::Translate(const XeVector2 &a)
{
    return XeMatrix(  1,   0, 0, 0,
                    0,   1, 0, 0,
                    0,   0, 1, 0,
                  a.x, a.y, 0, 1);
}

XeMatrix XeMatrix::Translate(const XeVector3 &a)
{
    return XeMatrix(  1,   0,   0, 0,
                    0,   1,   0, 0,
                    0,   0,   1, 0,
                  a.x, a.y, a.z, 1);
}

XeMatrix XeMatrix::Translate(const XeVector4 &a)
{
    return XeMatrix(  1,   0,   0, 0,
                    0,   1,   0, 0,
                    0,   0,   1, 0,
                  a.x, a.y, a.z, 1);
}

XeMatrix XeMatrix::Translate(float x, float y)
{
    return XeMatrix(1, 0, 0, 0,
                  0, 1, 0, 0,
                  0, 0, 1, 0,
                  x, y, 0, 1);
}

XeMatrix XeMatrix::Translate(float x, float y, float z)
{
    return XeMatrix(1, 0, 0, 0,
                  0, 1, 0, 0,
                  0, 0, 1, 0,
                  x, y, z, 1);
}

XeMatrix XeMatrix::Add(const XeMatrix &m1, const XeMatrix &m2)
{
    XeMatrix m;

    for (int i = 0; i < 16; ++i)
        m.m[i] = m1.m[i] + m2.m[i];

    return m;
}

XeMatrix XeMatrix::Subtract(const XeMatrix &m1, const XeMatrix &m2)
{
    XeMatrix m;

    for (int i = 0; i < 16; ++i)
        m.m[i] = m1.m[i] - m2.m[i];

    return m;
}

XeMatrix XeMatrix::Multiply(const XeMatrix &m, float a)
{
    XeMatrix out;

    for (int i = 0; i < 16; ++i)
        out.m[i] = a * m.m[i];

    return out;
}

XeMatrix XeMatrix::Multiply(const XeMatrix &m1, const XeMatrix &m2)
{
    XeMatrix m;
    m.m11 = (((m1.m11 * m2.m11) + (m1.m12 * m2.m21)) + (m1.m13 * m2.m31)) + (m1.m14 * m2.m41);
    m.m12 = (((m1.m11 * m2.m12) + (m1.m12 * m2.m22)) + (m1.m13 * m2.m32)) + (m1.m14 * m2.m42);
    m.m13 = (((m1.m11 * m2.m13) + (m1.m12 * m2.m23)) + (m1.m13 * m2.m33)) + (m1.m14 * m2.m43);
    m.m14 = (((m1.m11 * m2.m14) + (m1.m12 * m2.m24)) + (m1.m13 * m2.m34)) + (m1.m14 * m2.m44);
    m.m21 = (((m1.m21 * m2.m11) + (m1.m22 * m2.m21)) + (m1.m23 * m2.m31)) + (m1.m24 * m2.m41);
    m.m22 = (((m1.m21 * m2.m12) + (m1.m22 * m2.m22)) + (m1.m23 * m2.m32)) + (m1.m24 * m2.m42);
    m.m23 = (((m1.m21 * m2.m13) + (m1.m22 * m2.m23)) + (m1.m23 * m2.m33)) + (m1.m24 * m2.m43);
    m.m24 = (((m1.m21 * m2.m14) + (m1.m22 * m2.m24)) + (m1.m23 * m2.m34)) + (m1.m24 * m2.m44);
    m.m31 = (((m1.m31 * m2.m11) + (m1.m32 * m2.m21)) + (m1.m33 * m2.m31)) + (m1.m34 * m2.m41);
    m.m32 = (((m1.m31 * m2.m12) + (m1.m32 * m2.m22)) + (m1.m33 * m2.m32)) + (m1.m34 * m2.m42);
    m.m33 = (((m1.m31 * m2.m13) + (m1.m32 * m2.m23)) + (m1.m33 * m2.m33)) + (m1.m34 * m2.m43);
    m.m34 = (((m1.m31 * m2.m14) + (m1.m32 * m2.m24)) + (m1.m33 * m2.m34)) + (m1.m34 * m2.m44);
    m.m41 = (((m1.m41 * m2.m11) + (m1.m42 * m2.m21)) + (m1.m43 * m2.m31)) + (m1.m44 * m2.m41);
    m.m42 = (((m1.m41 * m2.m12) + (m1.m42 * m2.m22)) + (m1.m43 * m2.m32)) + (m1.m44 * m2.m42);
    m.m43 = (((m1.m41 * m2.m13) + (m1.m42 * m2.m23)) + (m1.m43 * m2.m33)) + (m1.m44 * m2.m43);
    m.m44 = (((m1.m41 * m2.m14) + (m1.m42 * m2.m24)) + (m1.m43 * m2.m34)) + (m1.m44 * m2.m44);

    return m;
}

XeMatrix XeMatrix::Divide(const XeMatrix &m, float amount)
{
    return XeMatrix::Multiply(m, 1.f / amount);
}

XeMatrix XeMatrix::Negate(const XeMatrix &m)
{
    return XeMatrix::Multiply(m, -1.f);
}

bool XeMatrix::Equal(const XeMatrix &m1, const XeMatrix &m2, float epsilon)
{
    for (int i = 0; i < 16; i++)
        if (fabs(m1.m[i] - m2.m[i]) > epsilon)
            return false;
    return true;
}

bool XeMatrix::NotEqual(const XeMatrix &m1, const XeMatrix &m2, float epsilon)
{
    return !XeMatrix::Equal(m1, m2, epsilon);
}

float XeMatrix::Determinant(const XeMatrix &m)
{
    float d1 = (m.m33 * m.m44) - (m.m34 * m.m43);
    float d2 = (m.m32 * m.m44) - (m.m34 * m.m42);
    float d3 = (m.m32 * m.m43) - (m.m33 * m.m42);
    float d4 = (m.m31 * m.m44) - (m.m34 * m.m41);
    float d5 = (m.m31 * m.m43) - (m.m33 * m.m41);
    float d6 = (m.m31 * m.m42) - (m.m32 * m.m41);
    return ((((m.m11 * (((m.m22 * d1) - (m.m23 * d2)) + (m.m24 * d3)))
            - (m.m12 * (((m.m21 * d1) - (m.m23 * d4)) + (m.m24 * d5))))
            + (m.m13 * (((m.m21 * d2) - (m.m22 * d4)) + (m.m24 * d6))))
            - (m.m14 * (((m.m21 * d3) - (m.m22 * d5)) + (m.m23 * d6))));
}

XeMatrix XeMatrix::Invert(const XeMatrix &m)
{
    XeMatrix i;
    float n1 = (m.m33 * m.m44) - (m.m34 * m.m43);
    float n2 = (m.m32 * m.m44) - (m.m34 * m.m42);
    float n3 = (m.m32 * m.m43) - (m.m33 * m.m42);
    float n4 = (m.m31 * m.m44) - (m.m34 * m.m41);
    float n5 = (m.m31 * m.m43) - (m.m33 * m.m41);
    float n6 = (m.m31 * m.m42) - (m.m32 * m.m41);
    float n7 = ((m.m22 * n1) - (m.m23 * n2)) + (m.m24 * n3);
    float n8 = -(((m.m21 * n1) - (m.m23 * n4)) + (m.m24 * n5));
    float n9 = ((m.m21 * n2) - (m.m22 * n4)) + (m.m24 * n6);
    float n10 = -(((m.m21 * n3) - (m.m22 * n5)) + (m.m23 * n6));
    float n11 = 1.f / ((((m.m11 * n7) + (m.m12 * n8)) + (m.m13 * n9)) + (m.m14 * n10));
    i.m11 = n7 * n11;
    i.m21 = n8 * n11;
    i.m31 = n9 * n11;
    i.m41 = n10 * n11;
    i.m12 = -(((m.m12 * n1) - (m.m13 * n2)) + (m.m14 * n3)) * n11;
    i.m22 = (((m.m11 * n1) - (m.m13 * n4)) + (m.m14 * n5)) * n11;
    i.m32 = -(((m.m11 * n2) - (m.m12 * n4)) + (m.m14 * n6)) * n11;
    i.m42 = (((m.m11 * n3) - (m.m12 * n5)) + (m.m13 * n6)) * n11;
    float n12 = (m.m23 * m.m44) - (m.m24 * m.m43);
    float n13 = (m.m22 * m.m44) - (m.m24 * m.m42);
    float n14 = (m.m22 * m.m43) - (m.m23 * m.m42);
    float n15 = (m.m21 * m.m44) - (m.m24 * m.m41);
    float n16 = (m.m21 * m.m43) - (m.m23 * m.m41);
    float n17 = (m.m21 * m.m42) - (m.m22 * m.m41);
    i.m13 = (((m.m12 * n12) - (m.m13 * n13)) + (m.m14 * n14)) * n11;
    i.m23 = -(((m.m11 * n12) - (m.m13 * n15)) + (m.m14 * n16)) * n11;
    i.m33 = (((m.m11 * n13) - (m.m12 * n15)) + (m.m14 * n17)) * n11;
    i.m43 = -(((m.m11 * n14) - (m.m12 * n16)) + (m.m13 * n17)) * n11;
    float n18 = (m.m23 * m.m34) - (m.m24 * m.m33);
    float n19 = (m.m22 * m.m34) - (m.m24 * m.m32);
    float n20 = (m.m22 * m.m33) - (m.m23 * m.m32);
    float n21 = (m.m21 * m.m34) - (m.m24 * m.m31);
    float n22 = (m.m21 * m.m33) - (m.m23 * m.m31);
    float n23 = (m.m21 * m.m32) - (m.m22 * m.m31);
    i.m14 = -(((m.m12 * n18) - (m.m13 * n19)) + (m.m14 * n20)) * n11;
    i.m24 = (((m.m11 * n18) - (m.m13 * n21)) + (m.m14 * n22)) * n11;
    i.m34 = -(((m.m11 * n19) - (m.m12 * n21)) + (m.m14 * n23)) * n11;
    i.m44 = (((m.m11 * n20) - (m.m12 * n22)) + (m.m13 * n23)) * n11;
    return i;
}

XeMatrix XeMatrix::Transpose(const XeMatrix &m)
{
    XeMatrix t = m;

    float tmp;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < i; j++)
        {
            tmp = t.m[4*i + j];
            t.m[4*i + j] = t.m[4*j + i];
            t.m[4*j + i] = tmp;
        }
    }

    return t;
}

XeMatrix XeMatrix::Lerp(const XeMatrix &m1, const XeMatrix &m2, float amount)
{
    return XeMatrix::Add(XeMatrix::Multiply(m1, 1.f - amount), XeMatrix::Multiply(m2, amount));
}

XeMatrix::XeMatrix()
{
    m11 = m22 = m33 = m44 = 1;
    m12 = m13 = m14 = m21 = m23 = m24 = m31 = m32 = m34 = m41 = m42 = m43 = 0;
}

XeMatrix::XeMatrix(float m11, float m12, float m13, float m14,
               float m21, float m22, float m23, float m24,
               float m31, float m32, float m33, float m34,
               float m41, float m42, float m43, float m44)
{
    this->m11 = m11;
    this->m12 = m12;
    this->m13 = m13;
    this->m14 = m14;
    this->m21 = m21;
    this->m22 = m22;
    this->m23 = m23;
    this->m24 = m24;
    this->m31 = m31;
    this->m32 = m32;
    this->m33 = m33;
    this->m34 = m34;
    this->m41 = m41;
    this->m42 = m42;
    this->m43 = m43;
    this->m44 = m44;
}

XeVector3 XeMatrix::up() const
{
    return XeMatrix::Up(*this);
}

XeVector3 XeMatrix::down() const
{
    return XeMatrix::Down(*this);
}

XeVector3 XeMatrix::left() const
{
    return XeMatrix::Left(*this);
}

XeVector3 XeMatrix::right() const
{
    return XeMatrix::Right(*this);
}

XeVector3 XeMatrix::forward() const
{
    return XeMatrix::Forward(*this);
}

XeVector3 XeMatrix::backward() const
{
    return XeMatrix::Backward(*this);
}

XeVector3 XeMatrix::translation() const
{
    return XeMatrix::Translation(*this);
}

XeMatrix XeMatrix::scale(float amount) const
{
    return *this * XeMatrix::Scale(amount);
}

XeMatrix XeMatrix::scale(const XeVector3 &amounts) const
{
    return *this * XeMatrix::Scale(amounts);
}

XeMatrix XeMatrix::rotateX(float angle) const
{
    return *this * XeMatrix::RotateX(angle);
}

XeMatrix XeMatrix::rotateY(float angle) const
{
    return *this * XeMatrix::RotateY(angle);
}

XeMatrix XeMatrix::rotateZ(float angle) const
{
    return *this * XeMatrix::RotateZ(angle);
}

XeMatrix XeMatrix::rotate(const XeVector3 &axis, float angle) const
{
    return *this * XeMatrix::FromAxisAngle(axis, angle);
}

XeMatrix XeMatrix::translate(const XeVector2 &amount) const
{
    return *this * XeMatrix::Translate(amount);
}

XeMatrix XeMatrix::translate(const XeVector3 &amount) const
{
    return *this * XeMatrix::Translate(amount);
}

XeMatrix XeMatrix::translate(const XeVector4 &amount) const
{
    return *this * XeMatrix::Translate(amount);
}

XeMatrix XeMatrix::translate(float x, float y) const
{
    return *this * XeMatrix::Translate(x, y);
}

XeMatrix XeMatrix::translate(float x, float y, float z) const
{
    return *this * XeMatrix::Translate(x, y, z);
}

float XeMatrix::determinant() const
{
    return XeMatrix::Determinant(*this);
}

XeMatrix XeMatrix::invert() const
{
    return XeMatrix::Invert(*this);
}

XeMatrix XeMatrix::transpose() const
{
    return XeMatrix::Transpose(*this);
}

bool XeMatrix::operator== (const XeMatrix& rhs) const
{
    return XeMatrix::Equal(*this, rhs);
}

bool XeMatrix::operator!= (const XeMatrix& rhs) const
{
    return XeMatrix::NotEqual(*this, rhs);
}

XeMatrix XeMatrix::operator+ (const XeMatrix& rhs) const
{
    return XeMatrix::Add(*this, rhs);
}

XeMatrix XeMatrix::operator- (const XeMatrix& rhs) const
{
    return XeMatrix::Subtract(*this, rhs);
}

XeMatrix XeMatrix::operator- () const
{
    return XeMatrix::Negate(*this);
}

XeMatrix XeMatrix::operator* (const XeMatrix& rhs) const
{
    return XeMatrix::Multiply(*this, rhs);
}

XeMatrix XeMatrix::operator* (float rhs) const
{
    return XeMatrix::Multiply(*this, rhs);
}

XeMatrix XeMatrix::operator/ (float rhs) const
{
    return XeMatrix::Divide(*this, rhs);
}

XeVector3 XeMatrix::operator* (const XeVector3& rhs) const
{
    return XeVector3::Transform(*this, rhs);
}

XeVector4 XeMatrix::operator* (const XeVector4& rhs) const
{
    return XeVector4::Transform(*this, rhs);
}

XeMatrix& XeMatrix::operator+= (const XeMatrix& rhs)
{
    for (int i = 0; i < 16; ++i)
        m[i] += rhs.m[i];

    return *this;
}

XeMatrix& XeMatrix::operator-= (const XeMatrix& rhs)
{
    for (int i = 0; i < 16; ++i)
        m[i] -= rhs.m[i];

    return *this;
}

XeMatrix& XeMatrix::operator*= (const XeMatrix& rhs)
{
    m11 = (((m11 * rhs.m11) + (m12 * rhs.m21)) + (m13 * rhs.m31)) + (m14 * rhs.m41);
    m12 = (((m11 * rhs.m12) + (m12 * rhs.m22)) + (m13 * rhs.m32)) + (m14 * rhs.m42);
    m13 = (((m11 * rhs.m13) + (m12 * rhs.m23)) + (m13 * rhs.m33)) + (m14 * rhs.m43);
    m14 = (((m11 * rhs.m14) + (m12 * rhs.m24)) + (m13 * rhs.m34)) + (m14 * rhs.m44);
    m21 = (((m21 * rhs.m11) + (m22 * rhs.m21)) + (m23 * rhs.m31)) + (m24 * rhs.m41);
    m22 = (((m21 * rhs.m12) + (m22 * rhs.m22)) + (m23 * rhs.m32)) + (m24 * rhs.m42);
    m23 = (((m21 * rhs.m13) + (m22 * rhs.m23)) + (m23 * rhs.m33)) + (m24 * rhs.m43);
    m24 = (((m21 * rhs.m14) + (m22 * rhs.m24)) + (m23 * rhs.m34)) + (m24 * rhs.m44);
    m31 = (((m31 * rhs.m11) + (m32 * rhs.m21)) + (m33 * rhs.m31)) + (m34 * rhs.m41);
    m32 = (((m31 * rhs.m12) + (m32 * rhs.m22)) + (m33 * rhs.m32)) + (m34 * rhs.m42);
    m33 = (((m31 * rhs.m13) + (m32 * rhs.m23)) + (m33 * rhs.m33)) + (m34 * rhs.m43);
    m34 = (((m31 * rhs.m14) + (m32 * rhs.m24)) + (m33 * rhs.m34)) + (m34 * rhs.m44);
    m41 = (((m41 * rhs.m11) + (m42 * rhs.m21)) + (m43 * rhs.m31)) + (m44 * rhs.m41);
    m42 = (((m41 * rhs.m12) + (m42 * rhs.m22)) + (m43 * rhs.m32)) + (m44 * rhs.m42);
    m43 = (((m41 * rhs.m13) + (m42 * rhs.m23)) + (m43 * rhs.m33)) + (m44 * rhs.m43);
    m44 = (((m41 * rhs.m14) + (m42 * rhs.m24)) + (m43 * rhs.m34)) + (m44 * rhs.m44);

    return *this;
}

XeMatrix& XeMatrix::operator*= (float rhs)
{
    for (int i = 0; i < 16; ++i)
        m[i] *= rhs;

    return *this;
}

XeMatrix& XeMatrix::operator/= (float rhs)
{
    return ((*this) *= (1.f / rhs));
}

XeMatrix operator*= (float lhs, const XeMatrix& rhs)
{
    return rhs * lhs;
}

XeMatrix operator/= (float lhs, const XeMatrix& rhs)
{
    return rhs * (1.f / lhs);
}

