#if !defined(VEC_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <initializer_list>

template <typename T, int N>
struct TVec
{
    T Data[N] = {};

    inline TVec() {}
    
    inline TVec(const std::initializer_list<T>& List)
    {
        int Counter = 0;
        for(auto& i : List)
        {
            Data[Counter++] = i;
            ASSERT(Counter != N);
        }
    }

    inline TVec(const TVec<T, N>& Vec)
    {
        for(auto i = 0; i < N; i++)
        {
            Data[i] = Vec.Data[i];
        }
    }

    inline TVec& operator=(const TVec<T, N>& Vec)
    {
        for(auto i = 0; i < N; i++)
        {
            Data[i] = Vec.Data[i];
        }
        return *this;
    }    
};

template <typename T>
struct TVec<T, 2>
{
    union
    {
        T Data[2] = {};

        struct
        {
            T x, y;
        };

        struct
        {
            T r, g;
        };

        struct
        {
            T a,  b;
        };
    };

    inline TVec<T, 2>() {}
    inline TVec<T, 2>(const T X, const T Y) : x(X), y(Y) {}
    inline TVec<T, 2>(const TVec<T, 2>& Vec) : x(Vec.x), y(Vec.y) {}
    inline TVec<T, 2>& operator=(const TVec<T, 2>& Vec)
    {
        x = Vec.x; y = Vec.y;
        return *this;
    }
};

template <typename T>
struct TVec<T, 3>
{
    union
    {
        T Data[3] = {};

        struct
        {
            T x, y, z;
        };

        struct
        {
            T r, g, b;
        };

        struct
        {
            T a, b, c;
        };
    };

    inline TVec<T, 3>() {}
    inline TVec<T, 3>(const T X, const T Y, const T Z) : x(X), y(Y), z(Z) {}
    inline TVec<T, 3>(const TVec<T, 3>& Vec) : x(Vec.x), y(Vec.y), z(Vec.z) {}
    inline TVec<T, 3>& operator=(const TVec<T, 3>& Vec)
    {
        x = Vec.x; y = Vec.y; z = Vec.z;
        return *this;
    }
};

template <typename T>
struct TVec<T, 4>
{
    union
    {
        T Data[4] = {};

        struct
        {
            T x, y, z, w;
        };

        struct
        {
            T r, g, b, a;
        };

        struct
        {
            T a, b, c, d;
        };
    };

    inline TVec<T, 4>() {}
    inline TVec<T, 4>(const T X, const T Y, const T Z, const T W) : x(X), y(Y), z(Z), w(W) {}
    inline TVec<T, 4>(const TVec<T, 4>& Vec) : x(Vec.x), y(Vec.y), z(Vec.z), w(Vec.w) {}
    inline TVec<T, 4>& operator=(const TVec<T, 4>& Vec)
    {
        x = Vec.x; y = Vec.y; z = Vec.z; w = Vec.w;
        return *this;
    }    
};

template <typename T, int N>
inline TVec<T, N> Add(const TVec<T, N>& Left, const T Right)
{
    TVec<T, N> Result;
    for(auto i = 0; i < N; i++)
    {
        Result.Data[i] = Left.Data[i] + Right;
    }
    return Result;
}

template <typename T, int N>
inline TVec<T, N> Add(const T Left, const TVec<T, N>& Right)
{
    return Add(Right, Left);
}

template <typename T, int N>
inline TVec<T, N> Add(const TVec<T, N>& Left, const TVec<T, N>& Right)
{
    TVec<T, N> Result;
    for(auto i = 0; i < N; i++)
    {
        Result.Data[i] = Left.Data[i] + Right.Data[i];
    }
    return Result;
}

template <typename T, int N>
inline TVec<T, N> Sub(const TVec<T, N>& Left, const T Right)
{
    TVec<T, N> Result;
    for(auto i = 0; i < N; i++)
    {
        Result.Data[i] = Left.Data[i] - Right;
    }
    return Result;
}

template <typename T, int N>
inline TVec<T, N> Sub(const TVec<T, N>& Left, const TVec<T, N>& Right)
{
    TVec<T, N> Result;
    for(auto i = 0; i < N; i++)
    {
        Result.Data[i] = Left.Data[i] - Right.Data[i];
    }
    return Result;
}

template <typename T, int N>
inline TVec<T, N> Mul(const TVec<T, N>& Left, const T Right)
{
    TVec<T, N> Result;
    for(auto i = 0; i < N; i++)
    {
        Result.Data[i] = Left.Data[i] * Right;
    }
    return Result;
}

template <typename T, int N>
inline TVec<T, N> Mul(const T Left, const TVec<T, N>& Right)
{
    return Mul(Right, Left);
}

template <typename T, int N>
inline TVec<T, N> Mul(const TVec<T, N>& Left, const TVec<T, N>& Right)
{
    TVec<T, N> Result;
    for(auto i = 0; i < N; i++)
    {
        Result.Data[i] = Left.Data[i] * Right.Data[i];
    }
    return Result;
}

template <typename T, int N>
inline TVec<T, N> Div(const TVec<T, N>& Left, const T Right)
{
    TVec<T, N> Result;
    for(auto i = 0; i < N; i++)
    {
        Result.Data[i] = Left.Data[i] / Right;
    }
    return Result;
}

template <typename T, int N>
inline TVec<T, N> Div(const TVec<T, N>& Left, const TVec<T, N>& Right)
{
    TVec<T, N> Result;
    for(auto i = 0; i < N; i++)
    {
        Result.Data[i] = Left.Data[i] / Right.Data[i];
    }
    return Result;
}

template <typename T, int N>
inline bool Equal(const TVec<T, N>& Left, const TVec<T, N>& Right)
{    
    for(auto i = 0; i < N; i++)
    {
        if(Left.Data[i] != Right.Data[i])
            return false;
    }
    return true;
}

template <typename T, int N>
inline bool NotEqual(const TVec<T, N>& Left, const TVec<T, N>& Right)
{
    return !Equal(Left, Right);
}

template <typename T, int N>
inline TVec<T, N> Negate(const TVec<T, N>& Vec)
{
    TVec<T, N> Result;
    for(auto i = 0; i < N; i++)
    {
        Result.Data[i] = -Vec.Data[i];
    }
    return Result;
}

template <typename T, int N>
inline TVec<T, N> operator+(const TVec<T, N>& Left, const T Right)
{
    return Add(Left, Right);
}

template <typename T, int N>
inline TVec<T, N> operator+(const T Left, const TVec<T, N>& Right)
{
    return Add(Left, Right);
}

template <typename T, int N>
inline TVec<T, N> operator+(const TVec<T, N>& Left, const TVec<T, N>& Right)
{
    return Add(Left, Right);
}

template <typename T, int N>
inline TVec<T, N> operator-(const TVec<T, N>& Left, const T Right)
{
    return Sub(Left, Right);
}

template <typename T, int N>
inline TVec<T, N> operator-(const T Left, const TVec<T, N>& Right)
{
    return Sub(Left, Right);
}

template <typename T, int N>
inline TVec<T, N> operator-(const TVec<T, N>& Left, const TVec<T, N>& Right)
{
    return Sub(Left, Right);
}

template <typename T, int N>
inline TVec<T, N> operator*(const TVec<T, N>& Left, const T Right)
{
    return Mul(Left, Right);
}

template <typename T, int N>
inline TVec<T, N> operator*(const T Left, const TVec<T, N>& Right)
{
    return Mul(Left, Right);
}

template <typename T, int N>
inline TVec<T, N> operator*(const TVec<T, N>& Left, const TVec<T, N>& Right)
{
    return Mul(Left, Right);
}

template <typename T, int N>
inline TVec<T, N> operator/(const TVec<T, N>& Left, const T Right)
{
    return Div(Left, Right);
}

template <typename T, int N>
inline TVec<T, N> operator/(const T Left, const TVec<T, N>& Right)
{
    return Div(Left, Right);
}

template <typename T, int N>
inline TVec<T, N> operator/(const TVec<T, N>& Left, const TVec<T, N>& Right)
{
    return Div(Left, Right);
}

template <typename T, int N>
inline bool operator==(const TVec<T, N>& Left, const TVec<T, N>& Right)
{
    return Equal(Left, Right);
}

template <typename T, int N>
inline bool operator!=(const TVec<T, N>& Left ,const TVec<T, N>& Right)
{
    return NotEqual(Left, Right);
}

template <typename T, int N>
inline TVec<T, N> operator-(const TVec<T, N>& Vec)
{
    return Negate(Vec);
}

template <typename T, int N>
inline TVec<T, N>& operator+=(TVec<T, N>& Vec, const T Right)
{
    for(auto i = 0; i < N; i++)
    {
        Vec.Data[i] += Right;
    }
    return Vec;
}

template <typename T, int N>
inline TVec<T, N>& operator+=(TVec<T, N>& Left, const TVec<T, N>& Right)
{
    for(auto i = 0; i < N; i++)
    {
        Left.Data[i] += Right.Data[i];
    }
    return Left;
}

template <typename T, int N>
inline TVec<T, N>& operator-=(TVec<T, N>& Vec, const T Right)
{
    for(auto i = 0; i < N; i++)
    {
        Vec.Data[i] -= Right;
    }
    return Vec;
}

template <typename T, int N>
inline TVec<T, N>& operator-=(TVec<T, N>& Left, const TVec<T, N>& Right)
{
    for(auto i = 0; i < N; i++)
    {
        Left.Data[i] -= Right.Data[i];
    }
    return Left;
}

template <typename T, int N>
inline TVec<T, N>& operator*=(TVec<T, N>& Vec, const T Right)
{
    for(auto i = 0; i < N; i++)
    {
        Vec.Data[i] *= Right;
    }
    return Vec;
}

template <typename T, int N>
inline TVec<T, N>& operator*=(TVec<T, N>& Left, const TVec<T, N>& Right)
{
    for(auto i = 0; i < N; i++)
    {
        Left.Data[i] *= Right.Data[i];
    }
    return Left;
}

template <typename T, int N>
inline TVec<T, N>& operator/=(TVec<T, N>& Vec, const T Right)
{
    for(auto i = 0; i < N; i++)
    {
        Vec.Data[i] /= Right;
    }
    return Vec;
}

template <typename T, int N>
inline TVec<T, N>& operator/=(TVec<T, N>& Left, const TVec<T, N>& Right)
{
    for(auto i = 0; i < N; i++)
    {
        Left.Data[i] /= Right.Data[i];
    }
    return Left;
}

template <typename T, int N>
inline T SqrMag(const TVec<T, N>& Vec)
{
    T Result = 0.0f;
    for(auto i = 0; i < N; i++)
    {
        Result += SQR(Vec.Data[i]);
    }
    return Result;
}

template <typename T, int N>
inline T Mag(const TVec<T, N>& Vec)
{
    return sqrt(SqrMag(Vec));
}

template <typename T, int N>
inline bool IsUnit(const TVec<T, N>& Vec)
{
    return (SqrMag(Vec) == 1) ? true : false;    
}

template <typename T, int N>
inline TVec<T, N> Norm(const TVec<T, N>& Vec)
{
    const T Length = Mag(Vec);
    return Div(Vec, Length);
}

template <typename T, int N>
inline T Dot(const TVec<T, N>& Left, const TVec<T, N>& Right)
{
    T Result = 0;
    for(auto i = 0; i < N; i++)
    {
        Result += (Left.Data[i]*Right.Data[i]);
    }
    return Result;
}

template <typename T, int N>
inline T Angle(const TVec<T, N>& Left, const TVec<T, N>& Right)
{
    const T DotProduct = Dot(Left, Right);
    const T Mag1 = Mag(Left);
    const T Mag2 = Mag(Right);
    return acos(DotProduct/(Mag1*Mag2));
}

template <typename T, int N>
inline TVec<T, N> Projection(const TVec<T, N>& P, const TVec<T, N>& Q)
{
    const T DotProduct = Dot(P, Q);
    const T LengthSqr = SqrMag(Q);
    return Mul(DotProduct/LengthSqr, Q);
}

template <typename T, int N>
inline TVec<T, N> Perpendicular(const TVec<T, N>& P, const TVec<T, N>& Q)
{
    return Sub(P, Projection(P, Q));
}

template <typename T>
inline TVec<T, 3> Cross(const TVec<T, 3>& Left, const TVec<T, 3>& Right)
{
    const T Lx = Left.x;
    const T Ly = Left.y;
    const T Lz = Left.z;
    const T Rx = Right.x;
    const T Ry = Right.y;
    const T Rz = Right.z;
    
    return TVec<T, 3>(Ly*Rz-Lz*Ry, Lz*Rx-Lx*Rz, Lx*Ry-Ly*Rx);
}

typedef TVec<int, 2> vec2i;
typedef TVec<int, 3> vec3i;
typedef TVec<int, 4> vec4i;

typedef TVec<float, 2> vec2f;
typedef TVec<float, 3> vec3f;
typedef TVec<float, 4> vec4f;

typedef TVec<double, 2> vec2d;
typedef TVec<double, 3> vec3d;
typedef TVec<double, 4> vec4d;

#define VEC_H
#endif
