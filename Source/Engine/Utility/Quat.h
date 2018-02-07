#if !defined(QUAT_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include "Vec.h"

template <typename T>
struct TQuat
{
    union
    {
        struct
        {
            T s;
            TVec<T, 3> v;
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

    inline TQuat() : a(T()), b(T()), c(T()), d(T())
    {}

    inline TQuat(const T A, const T B, const T C, const T D) : a(A), b(B), c(C), d(D)
    {}

    inline TQuat(const TQuat<T>& quat) : a(quat.a), b(quat.b), c(quat.c), d(quat.d)
    {}

    inline TQuat(const TVec<T, 4>& vec) : a(vec.x), b(vec.y), c(vec.z), d(vec.w)
    {}

    inline TQuat(const T Scalar, const TVec<T, 3>& vec) : w(Scalar), x(vec.x), y(vec.y), z(vec.z)
    {}

    inline TQuat& operator=(const TQuat<T>& quat)
    {
        a = quat.a;
        b = quat.b;
        c = quat.c;
        d = quat.d;
        return *this;
    }
    
    inline TQuat& operator=(const TVec<T, 4>& vec)
    {
        a = vec.x;
        b = vec.y;
        c = vec.z;
        d = vec.w;
        return *this;
    }    
};

template <typename T>
inline TQuat<T> Mul(const TQuat<T>& Left, const T Right)
{
    return TQuat<T>(Left.s*Right, Left.v*Right);
}

template <typename T>
inline TQuat<T> operator*(const TQuat<T>& Left, const T Right)
{
    return Mul(Left, Right);
}

template <typename T>
inline TQuat<T> operator*(const T Left, const TQuat<T>& Right)
{
    return Mul(Right, Left);
}

template <typename T>
inline TQuat<T> Div(const TQuat<T>& Left, const T Right)
{
    return TQuat<T>(Left.s/Right, Left.v/Right);
}

template <typename T>
inline TQuat<T> operator/(const TQuat<T>& Left, const T Right)
{
    return Div(Left, Right);
}

template <typename T>
inline TQuat<T> Mul(const TQuat<T>& Left, const TQuat<T>& Right)
{
    TQuat<T> Result;
    Result.s = Left.s*Right.s - Dot(Left.v, Right.v);
    Result.v = Left.s*Right.v + Right.s*Left.v + Cross(Left.v, Right.v);
    return Result;
}

template <typename T>
inline TQuat<T> operator*(const TQuat<T>& Left, const TQuat<T>& Right)
{
    return Mul(Left, Right);
}

template <typename T>
inline TQuat<T> Conjugate(const TQuat<T>& quat)
{
    return TQuat<T>(quat.s, -quat.v);
}

template <typename T>
inline T SqrMag(const TQuat<T>& quat)
{
    return SQR(quat.w) + SQR(quat.x) + SQR(quat.y) + SQR(quat.z);
}

template <typename T>
inline T Mag(const TQuat<T>& quat)
{
    return sqrt(SqrMag(quat));
}

template <typename T>
inline TQuat<T> Inverse(const TQuat<T>& quat)
{
    return Conjugate(quat)/SqrMag(quat);
}

template <typename T>
inline TQuat<T> Norm(const TQuat<T>& quat)
{
    T Length = Mag(quat);
    return quat/Length;
}

template <typename T>
inline TVec<T, 3> Rotate(const TQuat<T>& q, const TVec<T, 3>& v)
{
    T TempX, TempY, TempZ, TempW;
    TempX = (((q.a*v.x)+(q.c*v.z))-(q.d*v.y));
    TempY = (((q.a*v.y)+(q.d*v.x))-(q.b*v.z));
    TempZ = (((q.a*v.z)+(q.b*v.y))-(q.c*v.x));
    TempW = (((q.b*v.x)+(q.c*v.y))+(q.d*v.z));

    t_vec<T, 3> Result;
    Result.x = ((((TempW*q.b)+(TempX*q.a))-(TempY*q.d))+(TempZ*q.c));
    Result.y = ((((TempW*q.c)+(TempY*q.a))-(TempZ*q.b))+(TempX*q.d));
    Result.z = ((((TempW*q.d)+(TempZ*q.a))-(TempX*q.c))+(TempY*q.b));
    return Result;
}

typedef TQuat<int> quati;
typedef TQuat<float> quatf;
typedef TQuat<double> quatd;

#define QUAT_H
#endif
