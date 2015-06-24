#ifndef VECTOR2_H
#define VECTOR2_H

#include "xe/matrix.h"

/**
 * A 2D vector
 * @author Dave Kilian
 * @date 3 February 2011
 */
class XeVector2
{
public:
    union
    {
        struct { float x, y; };
        float xy[2];
    };

    /** Gets the vector (0, 0) */
    static const XeVector2& Zero();
    /** Gets the vector (1, 1) */
    static const XeVector2& One();
    /** Gets the vector (1, 0) */
    static const XeVector2& UnitX();
    /** Gets the vector (0, 1) */
    static const XeVector2& UnitY();

    /**
     * Computes the magnitude of a vector
     * @param v The vector whose magnitude is to be computed
     */
    static float Length(const XeVector2& v);
    /**
     * Computes the square of the magnitude of a vector.
     * This is less computationally intensive than computing the magnitude of
     * a vector (see XeVector2::Length()); when comparing magnitudes, always
     * use LengthSquared() instead of Length()
     * @param v The vector whose magnitude is to be computed
     */
    static float LengthSquared(const XeVector2& v);

    /**
     * Computes the dot product between two vectors
     * @param v1 A vector to dot with the other
     * @param v2 A vector to dot with the other
     */
    static float Dot(const XeVector2& v1, const XeVector2& v2);

    /**
     * Computes the distance between two vectors
     * @param v1 A vector to compute the distance between
     * @param v2 A vector to compute the distance between
     */
    static float Distance(const XeVector2& v1, const XeVector2& v2);
    /**
     * Computes the square of the distance between two vectors.
     * This is less computationally intensive than computing the distance betwen
     * two vectors (see XeVector2::Distance()). When comparing distances, always
     * use DistanceSquared() instead of Distance()
     * @param v1 A vector to compute the distance between
     * @param v2 A vector to compute the distance between
     */
    static float DistanceSquared(const XeVector2& v1, const XeVector2& v2);
    /**
     * Computes the Manhattan distance between two vectors. This can often be
     * used to compare distances relatively effectively and is less computationally
     * intensive than finding the distance or distance squared between two
     * vectors
     * @param v1 A vector to compute the Manhattan distance between
     * @param v2 A vector to compute the Manhattan distance between
     */
    static float ManhattanDistance(const XeVector2& v1, const XeVector2& v2);

    /**
     * Computes a vector with magnitude 1 pointing in the same direction as the given vector
     * @param v The vector to normalize
     * @return A new vector with the same direction as v and magnitude 1
     */
    static XeVector2 Normalize(const XeVector2& v);
    /**
     * Reflects a vector about another vector
     * @param v The vector to reflect
     * @param n The normal about which the vector should be reflected
     */
    static XeVector2 Reflect(const XeVector2& v, const XeVector2& n);

    /**
     * Checks whether two vectors are equal
     * @param v1 A vector to check for equality
     * @param v2 A vector to check for equality
     * @param epsilon The maximum difference between a component for which the two components
     *                are still considered equal. This corrects for floating point loss of precision
     */
    static bool Equal(const XeVector2& v1, const XeVector2& v2, float epsilon = 1e-6f);

    /**
     * Checks whether two vectors are not equal
     * @param v1 A vector to check for inequality
     * @param v2 A vector to check for inequality
     * @param epsilon The maximum difference between a component for which the two components
     *                are still considered equal. This corrects for floating point loss of precision
     */
    static bool NotEqual(const XeVector2& v1, const XeVector2& v2, float epsilon = 1e-6f);

    /**
     * Adds two vectors
     * @param v1 One of the vectors to add
     * @param v2 One of the vectors to add
     * @return A vector which is the sum of the two supplied vectors
     */
    static XeVector2 Add(const XeVector2& v1, const XeVector2& v2);
    /**
     * Subtracts a vector from another vector
     * @param v1 The vector to subtract from
     * @param v2 The vector to subtract
     * @return A vector which is the difference between v1 and v2
     */
    static XeVector2 Subtract(const XeVector2& v1, const XeVector2& v2);
    /**
     * Negates a vector
     * @param v The vector to be negated
     * @return A vector with the same length as [v] that points in the opposite direction
     */
    static XeVector2 Negate(const XeVector2& v);
    /**
     * Multiplies a vector by a scalar
     * @param v The vector to multiply
     * @param amount The scalar to multiply the vector by
     * @return A vector with the same direction as [v] with a magnitude of [v].length() * amount
     */
    static XeVector2 Multiply(const XeVector2& v, float amount);
    /**
     * Divides a vector by a scalar
     * @param v The vector to multiply
     * @param amount The scalar to divide the vector by
     * @return A vector with the same direction as [v] with a magnitude of [v].length() / amount
     */
    static XeVector2 Divide(const XeVector2& v, float amount);

    /**
     * Computes the linear interpolation between two vectors
     * @param v1 The first interpolation position
     * @param v2 The second interpolation position
     * @param amount The fractional interpolation position to produce
     */
    static XeVector2 Lerp(const XeVector2& v1, const XeVector2& v2, float amount);

    /**
     * Clamps a vector to a minimum and maximum, on a per-component basis
     * @param v The vector to clamp
     * @param min The minimum bound to clamp to
     * @param max The maximum bound to clamp to
     * @return The clamped vector
     */
    static XeVector2 Clamp(const XeVector2& v, const XeVector2& min, const XeVector2& max);
    /**
     * Computes the vectors whose components are the minimum components of the given vectors
     * @param v1 One of the vectors
     * @param v2 One of the vectors
     */
    static XeVector2 Min(const XeVector2& v1, const XeVector2& v2);
    /**
     * Computes the vectors whose components are the maximum components of the given vectors
     * @param v1 One of the vectors
     * @param v2 One of the vectors
     */
    static XeVector2 Max(const XeVector2& v1, const XeVector2& v2);

    /**
     * Computes a matrix-vector product
     * @param m The matrix factor
     * @param v The vector factor
     * @return The matrix-vector product
     */
    static XeVector2 Transform(const XeMatrix& m, const XeVector2& v);
    /**
     * Computes a magnitude-preserving matrix-vector product
     * @param m The matrix factor
     * @param v The vector factor
     * @return The matrix-vector product
     */
    static XeVector2 TransformNormal(const XeMatrix& m, const XeVector2& v);

    /**
     * Creates a new vector with (x, y) = (0, 0)
     */
    XeVector2();
    /**
     * Creates a vector
     * @param x The X component to assign to the vector created
     * @param y The Y component to assign to the vector created
     */
    XeVector2(float x, float y);

    /** Computes the magnitude of this vector */
    float length() const;
    /** Computes the square of the magnitude of this vector */
    float lengthSquared() const;

    /** Computes the dot product between this vector and another vector */
    float dot(const XeVector2& other) const;

    /** Computes the distance between this vector and another vector */
    float distanceTo(const XeVector2& other) const;
    /** Computes the square of the distance between this vector and another vector */
    float distanceSquaredTo(const XeVector2& other) const;
    /** Computes the Manhattan distance between this vector and another vector */
    float manhattanDistanceTo(const XeVector2& other) const;

    /** Creates a vector that points in the same direction as this vector, with magnitude 1 */
    XeVector2 normalize() const;
    /** Creates a vector representing this vector reflected about the given normal vector */
    XeVector2 reflect(const XeVector2& n) const;

    /** Compares this vector with another for equality */
    bool operator== (const XeVector2& rhs) const;
    /** Compares this vector with another for inequality */
    bool operator!= (const XeVector2& rhs) const;

    /** Computes the sum of this vector and another vector */
    XeVector2 operator+ (const XeVector2& rhs) const;
    /** Computes the difference between this vector and another vector */
    XeVector2 operator- (const XeVector2& rhs) const;
    /** Computes the negation of this vector */
    XeVector2 operator- () const;
    /** Computes the scalar-vector multiplication of this vector and a scalar */
    XeVector2 operator* (float rhs) const;
    /** Computes the scalar-vector division of this vector and a scalar */
    XeVector2 operator/ (float rhs) const;

    /** Adds a vector to this vector */
    XeVector2& operator+= (const XeVector2& rhs);
    /** Subtracts a vector from this vector */
    XeVector2& operator-= (const XeVector2& rhs);
    /** Multiplies the magnitude of this vector by the given value */
    XeVector2& operator*= (float rhs);
    /** Divides the magnitude of this vector by the given value */
    XeVector2& operator/= (float rhs);

    /** Computes a vector whose components are clamped to the given minimum and maximum values */
    XeVector2 clamp(const XeVector2& min, const XeVector2& max);

    /** Computes a matrix-vector multiplication */
    XeVector2 transform(const XeMatrix& m);
    /** Computes a magnitude-preserving matrix-vector multiplication */
    XeVector2 transformNormal(const XeMatrix& m);
};

/** Computes a scalar-vector multiplication */
XeVector2 operator* (float lhs, const XeVector2& rhs);

#endif // VECTOR2_H
