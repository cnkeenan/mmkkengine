#if !defined(QUAT_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include "Vec.h"

template <typename T>
struct TQuaternion
{
    union
    {
        struct
        {
            T s;
            TVector<T, 3> v;
        };
        
        struct
        {
            T w, x, y, z;
        };

        struct
        {
            T a, b, c, d;
        };
    };

    inline TQuaternion() : a(T()), b(T()), c(T()), d(T())
    {}

    inline TQuaternion(const T A, const T B, const T C, const T D) : a(A), b(B), c(C), d(D)
    {}

    inline TQuaternion(const TQuaternion<T>& quat) : a(quat.a), b(quat.b), c(quat.c), d(quat.d)
    {}

    inline TQuaternion(const TVector<T, 4>& vec) : a(vec.x), b(vec.y), c(vec.z), d(vec.w)
    {}

    inline TQuaternion(const T Scalar, const TVector<T, 3>& vec) : w(Scalar), x(vec.x), y(vec.y), z(vec.z)
    {}

    inline TQuaternion& operator=(const TQuaternion<T>& quat)
    {
        a = quat.a;
        b = quat.b;
        c = quat.c;
        d = quat.d;
        return *this;
    }
    
    inline TQuaternion& operator=(const TVector<T, 4>& vec)
    {
        a = vec.x;
        b = vec.y;
        c = vec.z;
        d = vec.w;
        return *this;
    }    
};

template <typename T>
inline TQuaternion<T> Mul(const TQuaternion<T>& Left, const T Right)
{
    return TQuaternion<T>(Left.s*Right, Left.v*Right);
}

template <typename T>
inline TQuaternion<T> operator*(const TQuaternion<T>& Left, const T Right)
{
    return Mul(Left, Right);
}

template <typename T>
inline TQuaternion<T> operator*(const T Left, const TQuaternion<T>& Right)
{
    return Mul(Right, Left);
}

template <typename T>
inline TQuaternion<T> Div(const TQuaternion<T>& Left, const T Right)
{
    return TQuaternion<T>(Left.s/Right, Left.v/Right);
}

template <typename T>
inline TQuaternion<T> operator/(const TQuaternion<T>& Left, const T Right)
{
    return Div(Left, Right);
}

template <typename T>
inline TQuaternion<T> Mul(const TQuaternion<T>& Left, const TQuaternion<T>& Right)
{
    TQuaternion<T> Result;
    Result.s = Left.s*Right.s - Dot(Left.v, Right.v);
    Result.v = Left.s*Right.v + Right.s*Left.v + Cross(Left.v, Right.v);
    return Result;
}

template <typename T>
inline TQuaternion<T> operator*(const TQuaternion<T>& Left, const TQuaternion<T>& Right)
{
    return Mul(Left, Right);
}

template <typename T>
inline TQuaternion<T> Conjugate(const TQuaternion<T>& quat)
{
    return TQuaternion<T>(quat.s, -quat.v);
}

template <typename T>
inline T SqrMag(const TQuaternion<T>& quat)
{
    return SQR(quat.w) + SQR(quat.x) + SQR(quat.y) + SQR(quat.z);
}

template <typename T>
inline T Mag(const TQuaternion<T>& quat)
{
    return sqrt(SqrMag(quat));
}

template <typename T>
inline TQuaternion<T> Inverse(const TQuaternion<T>& quat)
{
    return Conjugate(quat)/SqrMag(quat);
}

template <typename T>
inline TQuaternion<T> Norm(const TQuaternion<T>& quat)
{
    T Length = Mag(quat);
    return quat/Length;
}

template <typename T>
inline TVector<T, 3> Rotate(const TQuaternion<T>& q, const TVector<T, 3>& v)
{
    T TempX, TempY, TempZ, TempW;
    TempX = (((q.a*v.x)+(q.c*v.z))-(q.d*v.y));
    TempY = (((q.a*v.y)+(q.d*v.x))-(q.b*v.z));
    TempZ = (((q.a*v.z)+(q.b*v.y))-(q.c*v.x));
    TempW = (((q.b*v.x)+(q.c*v.y))+(q.d*v.z));

    TVector<T, 3> Result;
    Result.x = ((((TempW*q.b)+(TempX*q.a))-(TempY*q.d))+(TempZ*q.c));
    Result.y = ((((TempW*q.c)+(TempY*q.a))-(TempZ*q.b))+(TempX*q.d));
    Result.z = ((((TempW*q.d)+(TempZ*q.a))-(TempX*q.c))+(TempY*q.b));
    return Result;
}

typedef TQuaternion<int> FQuaternioni;
typedef TQuaternion<float> FQuaternionf;
typedef TQuaternion<double> FQuaterniond;

#define QUAT_H
#endif
