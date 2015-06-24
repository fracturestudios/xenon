#ifndef MATRIX_H
#define MATRIX_H

class XeVector2;
class XeVector3;
class XeVector4;
class XeQuaternion;

/**
 * A 4x4 matrix
 * @author Dave Kilian
 * @date 3 February 2011
 */
class XeMatrix
{
public:
    union
    {
        struct
        {
            float m11, m12, m13, m14;
            float m21, m22, m23, m24;
            float m31, m32, m33, m34;
            float m41, m42, m43, m44;
        };

        float m[16];
    };

    /** Gets the identity matrix */
    static const XeMatrix& Identity();
    /** Gets the all-zeroes matrix */
    static const XeMatrix& Zero();

    /** Computes the up unit vector in a matrix's transformed space */
    static XeVector3 Up(const XeMatrix& m);
    /** Computes the down unit vector in a matrix's transformed space */
    static XeVector3 Down(const XeMatrix& m);
    /** Computes the left unit vector in a matrix's transformed space */
    static XeVector3 Left(const XeMatrix& m);
    /** Computes the right unit vector in a matrix's transformed space */
    static XeVector3 Right(const XeMatrix& m);
    /** Computes the forward unit vector in a matrix's transformed space */
    static XeVector3 Forward(const XeMatrix& m);
    /** Computes the backward unit vector in a matrix's transformed space */
    static XeVector3 Backward(const XeMatrix& m);
    /** Computes the translation of a matrix's transformed space */
    static XeVector3 Translation(const XeMatrix& m);

    /**
     * Creates a billboard transformation (i.e. an object that always faces the camera)
     * @param objectPos The position of the object to billboard
     * @param cameraPos The position of the camera
     * @param up The up vector from the camera's point of view
     */
    static XeMatrix Billboard(const XeVector3& objectPos, const XeVector3& cameraPos, const XeVector3& up);
    /**
     * Creates a rotation transformation of an angle about an axis
     * @param axis The axis to rotate about
     * @param angle The amount to rotate, in radians
     */
    static XeMatrix FromAxisAngle(const XeVector3& axis, float angle);
    /**
     * Creates a matrix representing the same transformation as a quaternion
     * @param q The quaternion to create a matrix transformation for
     */
    static XeMatrix FromXeQuaternion(const XeQuaternion& q);
    /**
     * Creates a rotation from Euler angles
     * @param yaw The rotation about the Y axis, in radians
     * @param pitch The rotation about the X axis, in radians
     * @param roll The rotation about the Z axis, in radians
     */
    static XeMatrix FromYawPitchRoll(float yaw, float pitch, float roll);
    /**
     * Creates a camera transformation
     * @param cameraPos The position of the viewer
     * @param targetPos The position of the object to look at
     * @param up The up vector from the camera's point of view
     */
    static XeMatrix LookAt(const XeVector3& cameraPos, const XeVector3& targetPos, const XeVector3& up);

    /**
     * Creates an orthographic projection matrix. Orthographic projections do not foreshorten the scene.
     * @param width The width of the projection
     * @param height The height of the projection
     * @param znear The position of the near plane
     * @param zfar The position of the far plane
     */
    static XeMatrix Orthographic(float width, float height, float znear, float zfar);
    /**
     * Creates a perspective projection matrix
     * @param width The width of the projection
     * @param height The height of the proejction
     * @param znear The position of the near plane
     * @param zfar The position of the far plane
     */
    static XeMatrix Perspective(float width, float height, float znear, float zfar);
    /**
     * Creates a perspective projection matrix with the given FOV angle
     * @param fieldOfView The angle swept out by the viewer's visible range, in radians
     * @param aspectRatio The ratio of the width of the viewport to the height of the viewport
     * @param znear The position of the near plane
     * @param zfar The position fo the far plane
     */
    static XeMatrix PerspectiveFieldOfView(float fieldOfView, float aspectRatio, float znear, float zfar);

    /** Creates a uniform scale transformation */
    static XeMatrix Scale(float amount);
    /** Creates a nonuniform scale transformation */
    static XeMatrix Scale(const XeVector3& amounts);
    /** Creates a nonuniform scale transformation */
    static XeMatrix Scale(float x, float y, float z);
    /** Creates a rotation transformation about the X axis */
    static XeMatrix RotateX(float angle);
    /** Creates a rotation transformation about the Y axis */
    static XeMatrix RotateY(float angle);
    /** Creates a rotation transformation about the Z axis */
    static XeMatrix RotateZ(float angle);
    /** Creates a translation transformation */
    static XeMatrix Translate(const XeVector2& amount);
    /** Creates a translation transformation */
    static XeMatrix Translate(const XeVector3& amount);
    /** Creates a translation transformation */
    static XeMatrix Translate(const XeVector4& amount);
    /** Creates a translation transformation */
    static XeMatrix Translate(float x, float y);
    /** Creates a translation transformation */
    static XeMatrix Translate(float x, float y, float z);

    /** Computes an entry-wise matrix sum */
    static XeMatrix Add(const XeMatrix& m1, const XeMatrix& m2);
    /** Computes an entry-wise matrix difference */
    static XeMatrix Subtract(const XeMatrix& m1, const XeMatrix& m2);
    /** Computes a matrix-scalar multiplication */
    static XeMatrix Multiply(const XeMatrix& m, float amount);
    /** Computes a matrix-matrix multiplication */
    static XeMatrix Multiply(const XeMatrix& m1, const XeMatrix& m2);
    /** Computes a matrix-scalar division */
    static XeMatrix Divide(const XeMatrix& m, float amount);
    /** Computes a matrix negation */
    static XeMatrix Negate(const XeMatrix& m);

    /** Checks two matrices for equality */
    static bool Equal(const XeMatrix& m1, const XeMatrix& m2, float epsilon = 1e-6f);
    /** Checks two matrices for inequality */
    static bool NotEqual(const XeMatrix& m1, const XeMatrix& m2, float epsilon = 1e-6f);

    /** Computes the determinant of a matrix */
    static float Determinant(const XeMatrix& m);
    /** Computes the inverse of a matrix */
    static XeMatrix Invert(const XeMatrix& m);
    /** Computes the transpose of a matrix */
    static XeMatrix Transpose(const XeMatrix& m);
    /** Computes the linear interpolation between two matrices */
    static XeMatrix Lerp(const XeMatrix& m1, const XeMatrix& m2, float amount);

    /** Creates a matrix whose entries are the identity matrix */
    XeMatrix();
    /** Creates a matrix with the given parameters */
    XeMatrix(float m11, float m12, float m13, float m14,
           float m21, float m22, float m23, float m24,
           float m31, float m32, float m33, float m34,
           float m41, float m42, float m43, float m44);

    /** Computes the up unit vector in this matrix's transformed space */
    XeVector3 up() const;
    /** Computes the down unit vector in this matrix's transformed space */
    XeVector3 down() const;
    /** Computes the left unit vector in this matrix's transformed space */
    XeVector3 left() const;
    /** Computes the right unit vector in this matrix's transformed space */
    XeVector3 right() const;
    /** Computes the forward unit vector in this matrix's transformed space */
    XeVector3 forward() const;
    /** Computes the backward unit vector in this matrix's transformed space */
    XeVector3 backward() const;
    /** Computes the translation vector of this matrix's transformed space */
    XeVector3 translation() const;

    /** Creates a matrix consisting of this matrix's transforms followed by a uniform scale */
    XeMatrix scale(float amount) const;
    /** Creates a matrix consisting of this matrix's transforms followed by a non-uniform scale */
    XeMatrix scale(const XeVector3& amounts) const;
    /** Creates a matrix consisting of this matrix's transforms followed by a rotation about the X axis */
    XeMatrix rotateX(float angle) const;
    /** Creates a matrix consisting of this matrix's transforms followed by a rotation about the Y axis */
    XeMatrix rotateY(float angle) const;
    /** Creates a matrix consisting of this matrix's transforms followed by a rotation about the Z axis */
    XeMatrix rotateZ(float angle) const;
    /** Creates a matrix consisting of this matrix's transforms followed by a rotation about an axis angle */
    XeMatrix rotate(const XeVector3& axis, float angle) const;
    /** Creates a matrix consisting of this matrix's transforms followed by a translation */
    XeMatrix translate(const XeVector2& amount) const;
    /** Creates a matrix consisting of this matrix's transforms followed by a translation */
    XeMatrix translate(const XeVector3& amount) const;
    /** Creates a matrix consisting of this matrix's transforms followed by a translation */
    XeMatrix translate(const XeVector4& amount) const;
    /** Creates a matrix consisting of this matrix's transforms followed by a translation */
    XeMatrix translate(float x, float y) const;
    /** Creates a matrix consisting of this matrix's transforms followed by a translation */
    XeMatrix translate(float x, float y, float z) const;

    /** Computes this matrix's determinant */
    float determinant() const;
    /** Computes the invert of this matrix */
    XeMatrix invert() const;
    /** Computes the transpose of this matrix */
    XeMatrix transpose() const;

    /** Checks two matrices for equality */
    bool operator== (const XeMatrix& rhs) const;
    /** Checks two matrices for inequality */
    bool operator!= (const XeMatrix& rhs) const;

    /** Computes the sum of two matrices */
    XeMatrix operator+ (const XeMatrix& rhs) const;
    /** Computes the difference between two matrices */
    XeMatrix operator- (const XeMatrix& rhs) const;
    /** Computes the negation of a matrix */
    XeMatrix operator- () const;
    /** Performs a scalar-matrix multiplication */
    XeMatrix operator* (float rhs) const;
    /** Performs a matrix-matrix multiplication */
    XeMatrix operator* (const XeMatrix& rhs) const;
    /** Performs a scalar-matrix division */
    XeMatrix operator/ (float rhs) const;

    /** Performs a matrix-vector multiplication */
    XeVector3 operator* (const XeVector3& rhs) const;
    /** Performs a matrix-vector multiplication */
    XeVector4 operator* (const XeVector4& rhs) const;

    /** Adds another matrix to this matrix */
    XeMatrix& operator+= (const XeMatrix& rhs);
    /** Subtracts another matrix from this matrix */
    XeMatrix& operator-= (const XeMatrix& rhs);
    /** Multiplies this matrix by a scalar */
    XeMatrix& operator*= (float rhs);
    /** Multiplies this matrix by another matrix */
    XeMatrix& operator*= (const XeMatrix& rhs);
    /** Divides this matrix by a scalar */
    XeMatrix& operator/= (float rhs);
};

/** Multiplies a matrix by a scalar */
XeMatrix operator* (float lhs, const XeMatrix& rhs);
/** Divides a matrix by a scalar */
XeMatrix operator/ (float lhs, const XeMatrix& rhs);

#endif // MATRIX_H
