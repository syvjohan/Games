
#ifndef GAmE_MatH_H
#define GAmE_MatH_H

#define Pi 3.141592562f
#define INLINE inline

#include <math.h>

struct Vec2
{
    union
    {
        struct
        {
            float x, y;
        };
        float v[2];
    };

    inline explicit Vec2(float s = 0.0f) {
        v[0] = v[1] = s;
    }
    
    inline Vec2(float x, float y) {
        v[0] = x;
        v[1] = y;
    }
    
    static inline float dot(const Vec2 &v0, const Vec2 &v1)
    {
        return v0.x * v1.x + v0.y * v1.y;
    }

    static inline float lengthSquared(const Vec2 &v)
    {
        return dot(v, v);
    }

    static inline float length(const Vec2 &v)
    {
        return sqrtf(dot(v, v));
    }

    static inline Vec2 normalize(const Vec2 &v)
    {
        float l = length(v);
        return Vec2(v.x / l, v.y / l);
    }

};


struct Vec3
{
    union
    {
        struct
        {
            float x, y, z;
        };
        float v[3];
    };


    inline explicit Vec3(float s = 0.0f) {
        v[0] = v[1] = v[2] = s;
    }
    
    inline Vec3(float x, float y, float z) {
        v[0] = x;
        v[1] = y;
        v[2] = z;
    }
    
    inline explicit operator Vec2() const
    {
        Vec2 result;
        result.x = x;
        result.y = y;
        return result;
        
    }
    
    static inline float dot(const Vec3 &v0, const Vec3 &v1)
    {
        return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
    }

    static inline float lengthSquared(const Vec3 &v)
    {
        return dot(v, v);
    }

    static inline float length(const Vec3 &v)
    {
        return sqrtf(dot(v, v));
    }

    static inline Vec3 normalize(const Vec3 &v)
    {
        float l = length(v);
        return Vec3(v.x / l, v.y / l, v.z / l);
    }

    static inline Vec3 cross(const Vec3 &v0, const Vec3 &v1)
    {
        Vec3 result;
        result.x = v0.y * v1.z - v0.z * v1.y;
        result.y = v0.z * v1.x - v0.x * v1.z;
        result.z = v0.x * v1.y - v0.y * v1.x;

        return result;
    }
};

struct Vec4
{
    union
    {
        struct
        {
            float x, y, z, w;    
        };
        struct
        {
            float R, G, B, A;
        };
        float v[4];
    };

    inline explicit Vec4(float s = 0.0f) {
        v[0] = v[1] = v[2] = v[3] = s;
    }
    
    inline Vec4(float x, float y, float z, float w) {
        v[0] = x;
        v[1] = y;
        v[2] = z;
        v[3] = w;
    }
    
    inline explicit operator Vec3() const
    {
        Vec3 result;
        result.x = x;
        result.y = y;
        result.z = z;
        return result;
    }

    
    static inline float dot(const Vec4 &v0, const Vec4 &v1)
    {
        return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z + v0.w * v1.w;
    }

    static inline float lengthSquared(const Vec4 &v)
    {
        return dot(v, v);
    }

    static inline float length(const Vec4 &v)
    {
        return sqrtf(dot(v, v));
    }

    static inline Vec4 lerp(const Vec4 &a, const Vec4 &b, float t)
    {
        Vec4 result;
        result.x = a.x + (b.x - a.x) * t;
        result.y = a.y + (b.y - a.y) * t;
        result.z = a.z + (b.z - a.z) * t;
        result.w = a.w + (b.w - a.w) * t;
    
        return result;
    }

};

// TODO: Rewrite matrices using single dimensional arrays.

struct Mat3
{

    float m[3][3];
    
    static inline Mat3 identity()
    {
        Mat3 result;
        result.m[0][0] = 1;
        result.m[0][1] = 0;
        result.m[0][2] = 0;

        result.m[1][0] = 0;
        result.m[1][1] = 1;
        result.m[1][2] = 0;

        result.m[2][0] = 0;
        result.m[2][1] = 0;
        result.m[2][2] = 1;
    
        return result;
    }

    static inline Mat3 rotationX(float Angle)
    {
        Mat3 result = identity();
        float cosAngle = cosf(Angle);
        float sinAngle = sinf(Angle);
    
        result.m[1][1] = cosAngle;
        result.m[1][2] = -sinAngle;
        result.m[2][1] = sinAngle;
        result.m[2][2] = cosAngle;
    
        return result;
    }

    static inline Mat3 rotationY(float Angle)
    {
        Mat3 result = identity();
        float cosAngle = cosf(Angle);
        float sinAngle = sinf(Angle);
    
        result.m[0][0] = cosAngle;
        result.m[0][2] = sinAngle;
        result.m[2][0] = -sinAngle;
        result.m[2][2] = cosAngle;
    
        return result;    
    }

    static inline Mat3 rotationZ(float Angle)
    {
        Mat3 result = identity();

        float cosAngle = cosf(Angle);
        float sinAngle = sinf(Angle);
    
        result.m[0][0] = cosAngle;
        result.m[0][1] = -sinAngle;
        result.m[1][0] = sinAngle;
        result.m[1][1] = cosAngle;
    
        return result;    
    }

    
    static inline Vec2 transformPoint(const Mat3 &m, const Vec2 &v)
    {
        Vec3 temp = { v.x, v.y, 1.0f };

        Vec2 result;
        result.x = Vec3::dot(Vec3(m.m[0][0], m.m[0][1], m.m[0][2]), temp);
        result.y = Vec3::dot(Vec3(m.m[1][0], m.m[1][1], m.m[1][2]), temp);

        return result;
    }

    static inline Vec2 transformVector(const Mat3 &m, const Vec2 &v)
    {
        Vec3 temp = { v.x, v.y, 0 };
        Vec2 result;

        result.x = Vec3::dot(Vec3(m.m[0][0], m.m[0][1], m.m[0][2]), temp);
        result.y = Vec3::dot(Vec3(m.m[1][0], m.m[1][1], m.m[1][2]), temp);
        return result;
    }

};

struct Mat4
{
    float m[4][4];
    
    static inline Mat4 identity()
    {
        Mat4 result;
        result.m[0][0] = 1.0f;
        result.m[0][1] = 0.0f;
        result.m[0][2] = 0.0f;
        result.m[0][3] = 0.0f;

        result.m[1][0] = 0.0f;
        result.m[1][1] = 1.0f;
        result.m[1][2] = 0.0f;
        result.m[1][3] = 0.0f;
    
        result.m[2][0] = 0.0f;
        result.m[2][1] = 0.0f;
        result.m[2][2] = 1.0f;
        result.m[2][3] = 0.0f;

        result.m[3][0] = 0.0f;
        result.m[3][1] = 0.0f;
        result.m[3][2] = 0.0f;
        result.m[3][3] = 1.0f;
    
        return result;
    }

    static inline Mat4 orthoLH(float left, float right, float top, float bottom, float zn, float zf)
    {
        // TODO: Depth calculation not tested at ALL.
        Mat4 result = identity();

        // Translation
        result.m[0][3] = -(right + left) / (right - left);
        result.m[1][3] = -(top + bottom) / (top - bottom);
        result.m[2][3] = -(zf + zn) / (zf - zn);

        // Scale
        result.m[0][0] = 2.0f / (right - left);
        result.m[1][1] = 2.0f / (top - bottom);
        result.m[2][2] = 2.0f / (zf - zn);
    
        return result;
    }

    static inline Mat4 lookAtLH(const Vec3 &eye, const Vec3 &target, const Vec3& up) {
        Mat4 result;

        return result;
    }

    static inline Mat4 perspectiveLH(const Vec3 &eye, const Vec3 &target, const Vec3& up) {
        Mat4 result;

        return result;
    }

    static inline Mat4 rotationX(float Angle)
    {
        Mat4 result = identity();
        float cosAngle = cosf(Angle);
        float sinAngle = sinf(Angle);
    
        result.m[1][1] = cosAngle;
        result.m[1][2] = -sinAngle;
        result.m[2][1] = sinAngle;
        result.m[2][2] = cosAngle;
    
        return result;
    }

    static inline Mat4 rotationY(float Angle)
    {
        Mat4 result = identity();
        float cosAngle = cosf(Angle);
        float sinAngle = sinf(Angle);
    
        result.m[0][0] = cosAngle;
        result.m[0][2] = sinAngle;
        result.m[2][0] = -sinAngle;
        result.m[2][2] = cosAngle;
    
        return result;    
    }

    static inline Mat4 rotationZ(float Angle)
    {
        Mat4 result = identity();

        float cosAngle = cosf(Angle);
        float sinAngle = sinf(Angle);
    
        result.m[0][0] = cosAngle;
        result.m[0][1] = sinAngle;
        result.m[1][0] = -sinAngle;
        result.m[1][1] = cosAngle;
    
        return result;    
    }

    static inline Mat4 translation(float x, float y, float z) {
        Mat4 result = identity();
        result.m[0][3] = x;
        result.m[1][3] = y;
        result.m[2][3] = z;
        return result;
    }
    
    static inline Vec3 transformPoint(const Mat4 &m, const Vec3 &v)
    {
        Vec4 temp = { v.x, v.y, v.z, 1 };

        Vec3 result;
        result.x = Vec4::dot(Vec4(m.m[0][0], m.m[0][1], m.m[0][2], m.m[0][3]), temp);
        result.y = Vec4::dot(Vec4(m.m[1][0], m.m[1][1], m.m[1][2], m.m[1][3]), temp);
        result.z = Vec4::dot(Vec4(m.m[2][0], m.m[2][1], m.m[2][2], m.m[2][3]), temp);

        return result;
    }

    static inline Vec3 transformVector(const Mat4 &m, const Vec3 &v)
    {
        Vec4 temp = { v.x, v.y, v.z, 0 };

        Vec3 result;

        result.x = Vec4::dot(Vec4(m.m[0][0], m.m[0][1], m.m[0][2], m.m[0][3]), temp);
        result.y = Vec4::dot(Vec4(m.m[1][0], m.m[1][1], m.m[1][2], m.m[1][3]), temp);
        result.z = Vec4::dot(Vec4(m.m[2][0], m.m[2][1], m.m[2][2], m.m[2][3]), temp);

        return result;
    }
};

// Negation
inline Vec2
operator-(const Vec2 &v0)
{
    Vec2 result = { -v0.x, -v0.y };
    return result;
}

inline Vec2
operator+(const Vec2 &v0, const Vec2 &v1)
{
    Vec2 result = { v0.x + v1.x, v0.y + v1.y };
    return result;
}

inline const Vec2&
operator+=(Vec2 &v0, const Vec2 &v1)
{
    v0 = v0 + v1;
    return v0;
}

inline Vec2
operator-(const Vec2 &v0, const Vec2 &v1)
{
    Vec2 result = { v0.x - v1.x, v0.y - v1.y };
    return result;
}

inline const Vec2&
operator-=(Vec2 &v0, const Vec2 &v1)
{
    v0 = v0 - v1;
    return v0;
}

inline Vec2
operator*(const Vec2 &v0, float S)
{
    Vec2 result = { v0.x * S, v0.y * S };
    return result;
}

inline const Vec2&
operator*=(Vec2 &v0, float S)
{
    v0 = v0 * S;
    return v0;
}

inline Vec2
operator/(const Vec2 &v0, float S)
{
    return v0 * (1.0f / S);
}


inline const Vec2&
operator/=(Vec2 &v0, float S)
{
    v0 = v0 / S;
    return v0;
}


// Negation
inline Vec3
operator-(const Vec3 &v0)
{
    Vec3 result = { -v0.x, -v0.y, -v0.z };
    return result;
}

inline Vec3
operator+(const Vec3 &v0, const Vec3 &v1)
{
    Vec3 result = { v0.x + v1.x, v0.y + v1.y, v0.z + v1.z };
    return result;
}

inline const Vec3&
operator+=(Vec3 &v0, const Vec3 &v1)
{
    v0 = v0 + v1;
    return v0;
}

inline Vec3
operator-(const Vec3 &v0, const Vec3 &v1)
{
    Vec3 result = { v0.x - v1.x, v0.y - v1.y, v0.z - v1.z };
    return result;
}

inline const Vec3&
operator-=(Vec3 &v0, const Vec3 &v1)
{
    v0 = v0 - v1;
    return v0;
}

inline Vec3
operator*(const Vec3 &v0, float S)
{
    Vec3 result = { v0.x * S, v0.y * S, v0.z * S };
    return result;
}

inline const Vec3&
operator*=(Vec3 &v0, float S)
{
    v0 = v0 * S;
    return v0;
}

inline Vec3
operator/(const Vec3 &v0, float S)
{
    return v0 * (1.0f / S);
}

inline const Vec3&
operator/=(Vec3 &v0, float S)
{
    v0 = v0 / S;
    return v0;
}

// Negation
inline Vec4
operator-(const Vec4 &v0)
{
    Vec4 result = { -v0.x, -v0.y, -v0.z, -v0.w };
    return result;
}

inline Vec4
operator+(const Vec4 &v0, const Vec4 &v1)
{
    Vec4 result = { v0.x + v1.x, v0.y + v1.y, v0.z + v1.z, v0.w + v1.w };
    return result;
}

inline const Vec4&
operator+=(Vec4 &v0, const Vec4 &v1)
{
    v0 = v0 + v1;
    return v0;
}

inline Vec4
operator-(const Vec4 &v0, const Vec4 &v1)
{
    Vec4 result = { v0.x - v1.x, v0.y - v1.y, v0.z - v1.z, v0.w - v1.w };
    return result;
}

inline const Vec4&
operator-=(Vec4 &v0, const Vec4 &v1)
{
    v0 = v0 - v1;
    return v0;
}

inline Vec4
operator*(const Vec4 &v0, float S)
{
    Vec4 result = { v0.x * S, v0.y * S, v0.z * S, v0.w * S };
    return result;
}

inline const Vec4&
operator*=(Vec4 &v0, float S)
{
    v0 = v0 * S;
    return v0;
}

inline Vec4
operator/(const Vec4 &v0, float S)
{
    return v0 * (1.0f / S);
}

inline const Vec4&
operator/=(Vec4 &v0, float S)
{
    v0 = v0 / S;
    return v0;
}


// Same as in GLSL/HLSL, modulates the Vectors.
inline Vec4
operator*(const Vec4 &v0, const Vec4 &v1)
{
    Vec4 result = { v0.x * v1.x, v0.y * v1.y, v0.z * v1.z, v0.w * v1.w };
    return result;
}


inline Mat3
operator*(const Mat3 &m0, const Mat3 &m1)
{
    Vec3 col0(m1.m[0][0], m1.m[1][0], m1.m[2][0]);
    Vec3 col1(m1.m[0][1], m1.m[1][1], m1.m[2][1]);
    Vec3 col2(m1.m[0][2], m1.m[1][2], m1.m[2][2]);

    Vec3 row0(m0.m[0][0], m0.m[0][1], m0.m[0][2]);
    Vec3 row1(m0.m[1][0], m0.m[1][1], m0.m[1][2]);
    Vec3 row2(m0.m[2][0], m0.m[2][1], m0.m[2][2]);

    Mat3 result;
    result.m[0][0] = Vec3::dot(row0, col0);
    result.m[0][1] = Vec3::dot(row0, col1);
    result.m[0][2] = Vec3::dot(row0, col2);

    result.m[1][0] = Vec3::dot(row1, col0);
    result.m[1][1] = Vec3::dot(row1, col1);
    result.m[1][2] = Vec3::dot(row1, col2);

    result.m[2][0] = Vec3::dot(row2, col0);
    result.m[2][1] = Vec3::dot(row2, col1);
    result.m[2][2] = Vec3::dot(row2, col2);

    return result;
}

inline Mat4 operator*(const Mat4 &m0, const Mat4 &m1) {
    Vec4 col0(m1.m[0][0], m1.m[1][0], m1.m[2][0], m1.m[3][0]);
    Vec4 col1(m1.m[0][1], m1.m[1][1], m1.m[2][1], m1.m[3][1]);
    Vec4 col2(m1.m[0][2], m1.m[1][2], m1.m[2][2], m1.m[3][2]);
    Vec4 col3(m1.m[0][3], m1.m[1][3], m1.m[2][3], m1.m[3][3]);

    Vec4 row0(m0.m[0][0], m0.m[0][1], m0.m[0][2], m0.m[0][3]);
    Vec4 row1(m0.m[1][0], m0.m[1][1], m0.m[1][2], m0.m[1][3]);
    Vec4 row2(m0.m[2][0], m0.m[2][1], m0.m[2][2], m0.m[2][3]);
    Vec4 row3(m0.m[3][0], m0.m[3][1], m0.m[3][2], m0.m[3][3]);

    
    Mat4 result;
    result.m[0][0] = Vec4::dot(row0, col0);
    result.m[0][1] = Vec4::dot(row0, col1);
    result.m[0][2] = Vec4::dot(row0, col2);
    result.m[0][3] = Vec4::dot(row0, col3);

    result.m[1][0] = Vec4::dot(row1, col0);
    result.m[1][1] = Vec4::dot(row1, col1);
    result.m[1][2] = Vec4::dot(row1, col2);
    result.m[1][3] = Vec4::dot(row1, col3);

    result.m[2][0] = Vec4::dot(row2, col0);
    result.m[2][1] = Vec4::dot(row2, col1);
    result.m[2][2] = Vec4::dot(row2, col2);
    result.m[2][3] = Vec4::dot(row2, col3);

    result.m[3][0] = Vec4::dot(row3, col0);
    result.m[3][1] = Vec4::dot(row3, col1);
    result.m[3][2] = Vec4::dot(row3, col2);
    result.m[3][3] = Vec4::dot(row3, col3);
    
    return result;
}

// inline Mat3*
// Mat3IsometricToScreen(float CameraIsox, float CameraIsoy, float Screenwidth, float ScreenHeight,
//                       float Tilewidth, float TileHeight, Mat3 *Out)
// {
//     Mat3Identity(Out);

//     // NOTE: Same Equation as the one we used to use in IsoToScreen
//     // v.x = m00 * vx + m01 * vy + m02 * vz
//     // v.y = m10 * vx + m11 * vy + m12 * vz
//     // ------
//     // v.x = Tw/2 * vx + -Tw/2 * vy + 0 * vz;
//     // v.x = TH/2 * vx + TH/2 * vy + 0 * vz;

//     float Scalex = (int)Tilewidth / 2;
//     float Scaley = (int)TileHeight / 2;
    
//     Out->m00 = Scalex;
//     Out->m01 = -Scalex;
//     Out->m10 = Scaley;
//     Out->m11 = Scaley;
//     Out->m02 = -(CameraIsox - CameraIsoy) * Scalex + (Screenwidth) / 2.0f;
//     Out->m12 = -(CameraIsox + CameraIsoy) * Scaley + (ScreenHeight) / 2.0f;
//     Out->m02 = (int)(Out->m02 + 0.5f);
//     Out->m12 = (int)(Out->m12 + 0.5f);
    
//     return Out;
// }

inline Vec3
operator*(const Mat3 &m, const Vec3 &v)
{
    Vec3 row0(m.m[0][0], m.m[0][1], m.m[0][2]);
    Vec3 row1(m.m[1][0], m.m[1][1], m.m[1][2]);
    Vec3 row2(m.m[2][0], m.m[2][1], m.m[2][2]);
    
    Vec3 result;
    result.x = Vec3::dot(row0, v);
    result.y = Vec3::dot(row1, v);
    result.z = Vec3::dot(row2, v);
    return result;
}

#ifdef GAmE_MatH_SImD
#include "xmmintrin.h"
// Performance test
inline Mat4
Mat4mulvalue(Mat4 A, Mat4 B)
{
    // NOTE:
    // This calculation tries to be a bit clever, basically we calculate the multiplication
    // in a transposed state, instead of calculating it row by row, column by column,
    // while trying to use simd to do the multiplications per entry,
    // we instead leverage simd to calculate an entire row in the resulting Matrix at once.
    Mat4 result;

    // Only needs to be loaded once.
    __m128 BCx = _mm_load_ps((float*)&B.row0);
    __m128 BCy = _mm_load_ps((float*)&B.row1);
    __m128 BCz = _mm_load_ps((float*)&B.row2);
    __m128 BCw = _mm_load_ps((float*)&B.row3);

    __m128 ARx;
    __m128 ARy;
    __m128 ARz;
    __m128 ARw;
            
    __m128 x;
    __m128 y;
    __m128 z;    
    __m128 w;
    
#define COmPUTE_ROw(INDEx)                  \
    ARx = _mm_set1_ps(A.row##INDEx.x);      \
    ARy = _mm_set1_ps(A.row##INDEx.y);      \
    ARz = _mm_set1_ps(A.row##INDEx.z);      \
    ARw = _mm_set1_ps(A.row##INDEx.w);      \
    x = _mm_mul_ps(ARx, BCx);               \
    y = _mm_mul_ps(ARy, BCy);               \
    z = _mm_mul_ps(ARz, BCz);               \
    w = _mm_mul_ps(ARw, BCw);               \
    _mm_storeu_ps((float*)&result.row##INDEx, _mm_add_ps(x, _mm_add_ps(y, _mm_add_ps(z, w))))

    // Calculate one ROw in resulting Matrix
    COmPUTE_ROw(0);
    
    // Calculate one ROw in resulting Matrix
    COmPUTE_ROw(1);

    // Calculate one ROw in resulting Matrix
    COmPUTE_ROw(2);
    
    // Calculate one ROw in resulting Matrix
    COmPUTE_ROw(3);

    return result;
}
#endif

#endif // !GAmE_MatH_H
