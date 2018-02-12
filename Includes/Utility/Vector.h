#if !defined(VEC_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <initializer_list>

template <typename T, int N>
struct TVector
{
    T Data[N] = {};

    inline TVector() {}
    
    inline TVector(const std::initializer_list<T>& List)
    {
        int Counter = 0;
        for(auto& i : List)
        {
            Data[Counter++] = i;
            ASSERT(Counter != N, "Size of list should not be larger than the vector");
        }
    }

    inline TVector(const TVector<T, N>& Vec)
    {
        for(auto i = 0; i < N; i++)
        {
            Data[i] = Vec.Data[i];
        }
    }

    inline TVector& operator=(const TVector<T, N>& Vec)
    {
        for(auto i = 0; i < N; i++)
        {
            Data[i] = Vec.Data[i];
        }
        return *this;
    }    
};

template <typename T>
struct TVector<T, 2>
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

    inline TVector<T, 2>() {}
    inline TVector<T, 2>(const T X, const T Y) : x(X), y(Y) {}
    inline TVector<T, 2>(const TVector<T, 2>& Vec) : x(Vec.x), y(Vec.y) {}
    inline TVector<T, 2>& operator=(const TVector<T, 2>& Vec)
    {
        x = Vec.x; y = Vec.y;
        return *this;
    }
};

template <typename T>
struct TVector<T, 3>
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

    inline TVector<T, 3>() {}
    inline TVector<T, 3>(const T X, const T Y, const T Z) : x(X), y(Y), z(Z) {}
    inline TVector<T, 3>(const TVector<T, 3>& Vec) : x(Vec.x), y(Vec.y), z(Vec.z) {}
    inline TVector<T, 3>& operator=(const TVector<T, 3>& Vec)
    {
        x = Vec.x; y = Vec.y; z = Vec.z;
        return *this;
    }
};

template <typename T>
struct TVector<T, 4>
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

    inline TVector<T, 4>() {}
    inline TVector<T, 4>(const T X, const T Y, const T Z, const T W) : x(X), y(Y), z(Z), w(W) {}
    inline TVector<T, 4>(const TVector<T, 4>& Vec) : x(Vec.x), y(Vec.y), z(Vec.z), w(Vec.w) {}
    inline TVector<T, 4>& operator=(const TVector<T, 4>& Vec)
    {
        x = Vec.x; y = Vec.y; z = Vec.z; w = Vec.w;
        return *this;
    }    
};

template <typename T, int N>
inline TVector<T, N> Add(const TVector<T, N>& Left, const T Right)
{
    TVector<T, N> Result;
    for(auto i = 0; i < N; i++)
    {
        Result.Data[i] = Left.Data[i] + Right;
    }
    return Result;
}

template <typename T, int N>
inline TVector<T, N> Add(const T Left, const TVector<T, N>& Right)
{
    return Add(Right, Left);
}

template <typename T, int N>
inline TVector<T, N> Add(const TVector<T, N>& Left, const TVector<T, N>& Right)
{
    TVector<T, N> Result;
    for(auto i = 0; i < N; i++)
    {
        Result.Data[i] = Left.Data[i] + Right.Data[i];
    }
    return Result;
}

template <typename T, int N>
inline TVector<T, N> Sub(const TVector<T, N>& Left, const T Right)
{
    TVector<T, N> Result;
    for(auto i = 0; i < N; i++)
    {
        Result.Data[i] = Left.Data[i] - Right;
    }
    return Result;
}

template <typename T, int N>
inline TVector<T, N> Sub(const TVector<T, N>& Left, const TVector<T, N>& Right)
{
    TVector<T, N> Result;
    for(auto i = 0; i < N; i++)
    {
        Result.Data[i] = Left.Data[i] - Right.Data[i];
    }
    return Result;
}

template <typename T, int N>
inline TVector<T, N> Mul(const TVector<T, N>& Left, const T Right)
{
    TVector<T, N> Result;
    for(auto i = 0; i < N; i++)
    {
        Result.Data[i] = Left.Data[i] * Right;
    }
    return Result;
}

template <typename T, int N>
inline TVector<T, N> Mul(const T Left, const TVector<T, N>& Right)
{
    return Mul(Right, Left);
}

template <typename T, int N>
inline TVector<T, N> Mul(const TVector<T, N>& Left, const TVector<T, N>& Right)
{
    TVector<T, N> Result;
    for(auto i = 0; i < N; i++)
    {
        Result.Data[i] = Left.Data[i] * Right.Data[i];
    }
    return Result;
}

template <typename T, int N>
inline TVector<T, N> Div(const TVector<T, N>& Left, const T Right)
{
    TVector<T, N> Result;
    for(auto i = 0; i < N; i++)
    {
        Result.Data[i] = Left.Data[i] / Right;
    }
    return Result;
}

template <typename T, int N>
inline TVector<T, N> Div(const TVector<T, N>& Left, const TVector<T, N>& Right)
{
    TVector<T, N> Result;
    for(auto i = 0; i < N; i++)
    {
        Result.Data[i] = Left.Data[i] / Right.Data[i];
    }
    return Result;
}

template <typename T, int N>
inline bool Equal(const TVector<T, N>& Left, const TVector<T, N>& Right)
{    
    for(auto i = 0; i < N; i++)
    {
        if(Left.Data[i] != Right.Data[i])
            return false;
    }
    return true;
}

template <typename T, int N>
inline bool NotEqual(const TVector<T, N>& Left, const TVector<T, N>& Right)
{
    return !Equal(Left, Right);
}

template <typename T, int N>
inline TVector<T, N> Negate(const TVector<T, N>& Vec)
{
    TVector<T, N> Result;
    for(auto i = 0; i < N; i++)
    {
        Result.Data[i] = -Vec.Data[i];
    }
    return Result;
}

template <typename T, int N>
inline TVector<T, N> operator+(const TVector<T, N>& Left, const T Right)
{
    return Add(Left, Right);
}

template <typename T, int N>
inline TVector<T, N> operator+(const T Left, const TVector<T, N>& Right)
{
    return Add(Left, Right);
}

template <typename T, int N>
inline TVector<T, N> operator+(const TVector<T, N>& Left, const TVector<T, N>& Right)
{
    return Add(Left, Right);
}

template <typename T, int N>
inline TVector<T, N> operator-(const TVector<T, N>& Left, const T Right)
{
    return Sub(Left, Right);
}

template <typename T, int N>
inline TVector<T, N> operator-(const T Left, const TVector<T, N>& Right)
{
    return Sub(Left, Right);
}

template <typename T, int N>
inline TVector<T, N> operator-(const TVector<T, N>& Left, const TVector<T, N>& Right)
{
    return Sub(Left, Right);
}

template <typename T, int N>
inline TVector<T, N> operator*(const TVector<T, N>& Left, const T Right)
{
    return Mul(Left, Right);
}

template <typename T, int N>
inline TVector<T, N> operator*(const T Left, const TVector<T, N>& Right)
{
    return Mul(Left, Right);
}

template <typename T, int N>
inline TVector<T, N> operator*(const TVector<T, N>& Left, const TVector<T, N>& Right)
{
    return Mul(Left, Right);
}

template <typename T, int N>
inline TVector<T, N> operator/(const TVector<T, N>& Left, const T Right)
{
    return Div(Left, Right);
}

template <typename T, int N>
inline TVector<T, N> operator/(const T Left, const TVector<T, N>& Right)
{
    return Div(Left, Right);
}

template <typename T, int N>
inline TVector<T, N> operator/(const TVector<T, N>& Left, const TVector<T, N>& Right)
{
    return Div(Left, Right);
}

template <typename T, int N>
inline bool operator==(const TVector<T, N>& Left, const TVector<T, N>& Right)
{
    return Equal(Left, Right);
}

template <typename T, int N>
inline bool operator!=(const TVector<T, N>& Left ,const TVector<T, N>& Right)
{
    return NotEqual(Left, Right);
}

template <typename T, int N>
inline TVector<T, N> operator-(const TVector<T, N>& Vec)
{
    return Negate(Vec);
}

template <typename T, int N>
inline TVector<T, N>& operator+=(TVector<T, N>& Vec, const T Right)
{
    for(auto i = 0; i < N; i++)
    {
        Vec.Data[i] += Right;
    }
    return Vec;
}

template <typename T, int N>
inline TVector<T, N>& operator+=(TVector<T, N>& Left, const TVector<T, N>& Right)
{
    for(auto i = 0; i < N; i++)
    {
        Left.Data[i] += Right.Data[i];
    }
    return Left;
}

template <typename T, int N>
inline TVector<T, N>& operator-=(TVector<T, N>& Vec, const T Right)
{
    for(auto i = 0; i < N; i++)
    {
        Vec.Data[i] -= Right;
    }
    return Vec;
}

template <typename T, int N>
inline TVector<T, N>& operator-=(TVector<T, N>& Left, const TVector<T, N>& Right)
{
    for(auto i = 0; i < N; i++)
    {
        Left.Data[i] -= Right.Data[i];
    }
    return Left;
}

template <typename T, int N>
inline TVector<T, N>& operator*=(TVector<T, N>& Vec, const T Right)
{
    for(auto i = 0; i < N; i++)
    {
        Vec.Data[i] *= Right;
    }
    return Vec;
}

template <typename T, int N>
inline TVector<T, N>& operator*=(TVector<T, N>& Left, const TVector<T, N>& Right)
{
    for(auto i = 0; i < N; i++)
    {
        Left.Data[i] *= Right.Data[i];
    }
    return Left;
}

template <typename T, int N>
inline TVector<T, N>& operator/=(TVector<T, N>& Vec, const T Right)
{
    for(auto i = 0; i < N; i++)
    {
        Vec.Data[i] /= Right;
    }
    return Vec;
}

template <typename T, int N>
inline TVector<T, N>& operator/=(TVector<T, N>& Left, const TVector<T, N>& Right)
{
    for(auto i = 0; i < N; i++)
    {
        Left.Data[i] /= Right.Data[i];
    }
    return Left;
}

template <typename T, int N>
inline T SqrMag(const TVector<T, N>& Vec)
{
    T Result = 0.0f;
    for(auto i = 0; i < N; i++)
    {
        Result += SQR(Vec.Data[i]);
    }
    return Result;
}

template <typename T, int N>
inline T Mag(const TVector<T, N>& Vec)
{
    return sqrt(SqrMag(Vec));
}

template <typename T, int N>
inline bool IsUnit(const TVector<T, N>& Vec)
{
    return (SqrMag(Vec) == 1) ? true : false;    
}

template <typename T, int N>
inline TVector<T, N> Norm(const TVector<T, N>& Vec)
{
    const T Length = Mag(Vec);
    return Div(Vec, Length);
}

template <typename T, int N>
inline T Dot(const TVector<T, N>& Left, const TVector<T, N>& Right)
{
    T Result = 0;
    for(auto i = 0; i < N; i++)
    {
        Result += (Left.Data[i]*Right.Data[i]);
    }
    return Result;
}

template <typename T, int N>
inline T Angle(const TVector<T, N>& Left, const TVector<T, N>& Right)
{
    const T DotProduct = Dot(Left, Right);
    const T Mag1 = Mag(Left);
    const T Mag2 = Mag(Right);
    return acos(DotProduct/(Mag1*Mag2));
}

template <typename T, int N>
inline TVector<T, N> Projection(const TVector<T, N>& P, const TVector<T, N>& Q)
{
    const T DotProduct = Dot(P, Q);
    const T LengthSqr = SqrMag(Q);
    return Mul(DotProduct/LengthSqr, Q);
}

template <typename T, int N>
inline TVector<T, N> Perpendicular(const TVector<T, N>& P, const TVector<T, N>& Q)
{
    return Sub(P, Projection(P, Q));
}

template <typename T>
inline TVector<T, 3> Cross(const TVector<T, 3>& Left, const TVector<T, 3>& Right)
{
    const T Lx = Left.x;
    const T Ly = Left.y;
    const T Lz = Left.z;
    const T Rx = Right.x;
    const T Ry = Right.y;
    const T Rz = Right.z;
    
    return TVector<T, 3>(Ly*Rz-Lz*Ry, Lz*Rx-Lx*Rz, Lx*Ry-Ly*Rx);
}

typedef TVector<int, 2> FVector2i;
typedef TVector<int, 3> FVector3i;
typedef TVector<int, 4> FVector4i;

typedef TVector<float, 2> FVector2f;
typedef TVector<float, 3> FVector3f;
typedef TVector<float, 4> FVector4f;

typedef TVector<double, 2> FVector2d;
typedef TVector<double, 3> FVector3d;
typedef TVector<double, 4> FVector4d;

#define VEC_H
#endif
