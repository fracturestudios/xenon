#ifndef QUATERNION_H
#define QUATERNION_H

#include "xe/matrix.h"
#include "xe/vector3.h"

/**
 * A quaternion. XeQuaternions are good for representing rotations, as they do not suffer from gimbal lock
 * @author Dave Kilian
 * @date 4 February 2011
 */
class XeQuaternion
{
public:
    union
    {
        struct { float x, y, z, w; };
        float xyzw[4];
    };

    /** Gets the identity quaternion */
    static const XeQuaternion& Identity();
    /** Gets the all-zeroes quaternion */
    static const XeQuaternion& Zero();

    /**
     * Creates a quaternion representing the rotation of an angle about an arbitrary axis
     * @param axis The to rotate about
     * @param angle The angle to rotate through, in radians
     */
    static XeQuaternion FromAxisAngle(const XeVector3& axis, float angle);
    /**
     * Creates a quaternion representing the same rotation as in the given matrix
     * @param m The matrix containing the rotation to convert
     */
    static XeQuaternion FromRotationXeMatrix(const XeMatrix& m);
    /**
     * Creates a quaternion representing the rotations of the given Euler angles
     * @param yaw The rotation about the Y axis
     * @param pitch The rotation about the X axis
     * @param roll The rotation about the Z axis
     */
    static XeQuaternion FromYawPitchRoll(float yaw, float pitch, float roll);

    /** Computes the magnitude of a quaternion */
    static float Length(const XeQuaternion& q);
    /** Computes the square of the magnitude of a quaternion */
    static float LengthSquared(const XeQuaternion& q);
    /** Computes a quaternion representing the same rotation as the given quaternion, but with length 1 */
    static XeQuaternion Normalize(const XeQuaternion& q);

    /** Comptues the sum of two quaternions */
    static XeQuaternion Add(const XeQuaternion& q1, const XeQuaternion& q2);
    /** Computes the difference between two quaternions */
    static XeQuaternion Subtract(const XeQuaternion& q1, const XeQuaternion& q2);
    /** Computes the quaternion representing the rotation of one quaternion followed by the rotation of another quaternion */
    static XeQuaternion Concatenate(const XeQuaternion& q1, const XeQuaternion& q2);
    /** Computes a quaternion-quaternion product */
    static XeQuaternion Multiply(const XeQuaternion& q1, const XeQuaternion& q2);
    /** Computes a scalar-quaternion product */
    static XeQuaternion Multiply(const XeQuaternion& q, float amount);
    /** Computes a quaternion-quaternion quotient */
    static XeQuaternion Divide(const XeQuaternion& q1, const XeQuaternion& q2);
    /** Computes a scalar-quaternion quotient */
    static XeQuaternion Divide(const XeQuaternion& q, float amount);
    /** Computes a quaternion with each component the negation of the same component of another quaternion */
    static XeQuaternion Negate(const XeQuaternion& q);

    /** Compares two quaternions for equality */
    static bool Equal(const XeQuaternion& q1, const XeQuaternion& q2, float epsilon = 1e-6);
    /** Compares two quaternions for inequality */
    static bool NotEqual(const XeQuaternion& q1, const XeQuaternion& q2, float epsilon = 1e-6);

    /** Computes the dot product of two quaternions */
    static float Dot(const XeQuaternion& q1, const XeQuaternion& q2);
    /** Computes a linear interpolation between two quaternions */
    static XeQuaternion Lerp(const XeQuaternion& q1, const XeQuaternion& q2, float amount);
    /** Computes a spherical-linear interpolation between two quaternions */
    static XeQuaternion Slerp(const XeQuaternion& q1, const XeQuaternion& q2, float amount);
    /** Computes the inverse of a quaternion */
    static XeQuaternion Invert(const XeQuaternion& q);
    /** Computes the conjugate of a quaternion */
    static XeQuaternion Conjugate(const XeQuaternion& q);

    /** Creates the identity quaternion */
    XeQuaternion();
    /** Creates a quaternion with the specified components */
    XeQuaternion(float x, float y, float z, float w);

    /** Computes the magnitude of this quaternion */
    float length() const;
    /** Computes the square of the magnitude of this quaternion */
    float lengthSquared() const;
    /** Creates a normalized copy of this quaternion */
    XeQuaternion normalize() const;

    /** Computes the dot product between this and another quaternoin */
    float dot(const XeQuaternion& other) const;
    /** Finds the inverse of this quaternion */
    XeQuaternion invert() const;
    /** Finds the conjugate of this quaternion */
    XeQuaternion conjugate() const;

    /** Checks two quaternions for equality */
    bool operator== (const XeQuaternion& rhs) const;
    /** Checks two quaternions for inequality */
    bool operator!= (const XeQuaternion& rhs) const;

    /** Computes a quaternion sum */
    XeQuaternion operator+ (const XeQuaternion& rhs) const;
    /** Computes a quaternion difference */
    XeQuaternion operator- (const XeQuaternion& rhs) const;
    /** Negates a quaternion */
    XeQuaternion operator- () const;
    /** Computes a quaternion-quaternion product */
    XeQuaternion operator* (const XeQuaternion& rhs) const;
    /** Computes a scalar-quaternion product */
    XeQuaternion operator* (float rhs) const;
    /** Computes a quaternion-quaternion quotient */
    XeQuaternion operator/ (const XeQuaternion& rhs) const;
    /** Computes a scalar-quaternion quotient */
    XeQuaternion operator/ (float rhs) const;

    /** Adds another quaternion to this one */
    XeQuaternion& operator+= (const XeQuaternion& rhs);
    /** Subtracts another quaternion to this one */
    XeQuaternion& operator-= (const XeQuaternion& rhs);
    /** Multiplies this quaternion by another one */
    XeQuaternion& operator*= (const XeQuaternion& rhs);
    /** Multiplies this quaternion by a scalar */
    XeQuaternion& operator*= (float rhs);
    /** Divides this quaternion by another one */
    XeQuaternion& operator/= (const XeQuaternion& rhs);
    /** Divides this quaternion by a scalar */
    XeQuaternion& operator/= (float rhs);
};

/** Computes a scalar-quaternion product */
XeQuaternion operator* (float lhs, const XeQuaternion& rhs);
/** Computes a scalar-quaternion quotient */
XeQuaternion operator/ (float lhs, const XeQuaternion& rhs);

#endif // QUATERNION_H
