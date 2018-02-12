#if !defined(MAT_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include "Vec.h"

template <typename T>
struct TQuaternion;

template <typename T, int Row, int Col>
struct TMatrix
{    
    union
    {        
        T Data[Row*Col] = {};
        TVector<T, Col> Rows[Row];
    };

    inline TMatrix() {}
    
    inline TMatrix(const TMatrix<T, Row, Col>& Matrix)
    {
        for(auto i = 0; i < Row*Col; i++)
        {
            Data[i] = Matrix.Data[i];
        }
    }

    inline TMatrix(const T Value)
    {
#pragma warning(push)
#pragma warning(disable:4127)
        ASSERT(Row == Col, "Must be a diagonal matrix");
#pragma warning(pop)
        
        for(auto i = 0; i < Row; i++)
        {
            for(auto j = 0; j < Col; j++)
            {
                if(i == j)
                {
                    Data[Row*i+j] = Value;
                }                
            }
        }
    }

    inline TMatrix(T* Array, int Size)
    {
        ASSERT((Row*Col) == Size, "Size of array must equal the matrix");
        int Counter = 0;
        for(auto& i : Array)
        {
            Data[Counter++] = i;
        }
    }

    inline TMatrix(const std::initializer_list<T>& List)
    {
        int Counter = 0;
        for(auto& i : List)
        {
            Data[Counter++] = i;
        }
    }
    
    inline TMatrix<T, Row, Col>& operator=(const TMatrix<T, Row, Col>& Matrix)
    {
        for(auto i = 0; i < Row*Col; i++)
        {
            Data[i] = Matrix.Data[i];
        }
        return *this;
    }

    inline T& operator[](const size_t Index)
    {
        return Data[Index];
    }
};

template <typename T, int Row, int Col>
inline TMatrix<T, Col, Row> Transpose(const TMatrix<T, Row, Col>& Mat);

template <typename T, int Row, int Col>
inline TMatrix<T, Row, Col> Add(const TMatrix<T, Row, Col>& Left, const T Right)
{
    TMatrix<T, Row, Col> Result;
    for(auto i = 0; i < Row*Col; i++)
    {
        Result.Data[i] = Left.Data[i] + Right;
    }
    return Result;
}


template <typename T, int Row, int Col>
inline TMatrix<T, Row, Col> Add(const T Left, const TMatrix<T, Row, Col>& Right)
{
    return Add(Right, Left);
}

template <typename T, int Row, int Col>
inline TMatrix<T, Row, Col> Add(const TMatrix<T, Row, Col>& Left, const TMatrix<T, Row, Col>& Right)
{
    TMatrix<T, Row, Col> Result;
    for(auto i = 0; i < Row*Col; i++)
    {
        Result.Data[i] = Left.Data[i] + Right.Data[i];
    }
    return Result;
}

template <typename T, int Row, int Col>
inline TMatrix<T, Row, Col> Sub(const TMatrix<T, Row, Col>& Left, const T Right)
{
    TMatrix<T, Row, Col> Result;
    for(auto i = 0; i < Row*Col; i++)
    {
        Result.Data[i] = Left.Data[i] - Right;
    }
    return Result;
}

template <typename T, int Row, int Col>
inline TMatrix<T, Row, Col> Sub(const TMatrix<T, Row, Col>& Left, const TMatrix<T, Row, Col>& Right)
{
    TMatrix<T, Row, Col> Result;
    for(auto i = 0; i < Row*Col; i++)
    {
        Result.Data[i] = Left.Data[i] - Right.Data[i];
    }
    return Result;
}

template <typename T, int Row, int Col>
inline TMatrix<T, Row, Col> Mul(const TMatrix<T, Row, Col>& Left, const T Right)
{
    TMatrix<T, Row, Col> Result;
    for(auto i = 0; i < Row*Col; i++)
    {
        Result.Data[i] = Left.Data[i] * Right;
    }
    return Result;
}


template <typename T, int Row, int Col>
inline TMatrix<T, Row, Col> Mul(const T Left, const TMatrix<T, Row, Col>& Right)
{
    return Mul(Right, Left);
}

template <typename T, int n, int m, int p>
inline TMatrix<T, n, p> Mul(const TMatrix<T, n, m>& Left, const TMatrix<T, m, p>& Right)
{
    TMatrix<T, n, p> Result;
    TMatrix<T, p, m> TransposeRight = Transpose(Right);
    for(auto i = 0; i < n; i++)
    {        
        for(auto j = 0; j < p; j++)
        {
            Result.Data[n*i+j] = Dot(Left.Rows[i], TransposeRight.Rows[j]);
        }
    }
    return Result;
}

template <typename T, int Row, int Col>
inline TMatrix<T, Row, Col> operator+(const TMatrix<T, Row, Col>& Left, const T Right)
{
    return Add(Left, Right);
}

template <typename T, int Row, int Col>
inline TMatrix<T, Row, Col> operator+(const T Left, const TMatrix<T, Row, Col>& Right)
{
    return Add(Right, Left);
}

template <typename T, int Row, int Col>
inline TMatrix<T, Row, Col> operator+(const TMatrix<T, Row, Col>& Left, const TMatrix<T, Row, Col>& Right)
{
    return Add(Left, Right);
}

template <typename T, int Row, int Col>
inline TMatrix<T, Row, Col> operator-(const TMatrix<T, Row, Col>& Left, const T Right)
{
    return Sub(Left, Right);
}

template <typename T, int Row, int Col>
inline TMatrix<T, Row, Col> operator-(const TMatrix<T, Row, Col>& Left, const TMatrix<T, Row, Col>& Right)
{
    return Sub(Left, Right);
}

template <typename T, int Row, int Col>
inline TMatrix<T, Row, Col> operator*(const TMatrix<T, Row, Col>& Left, const T Right)
{
    return Mul(Left, Right);
}

template <typename T, int Row, int Col>
inline TMatrix<T, Row, Col> operator*(const T Left, const TMatrix<T, Row, Col>& Right)
{
    return Mul(Right, Left);
}

template <typename T, int n, int m, int p>
inline TMatrix<T, n, p> operator*(const TMatrix<T, n, m>& Left, const TMatrix<T, m, p>& Right)
{
    return Mul(Left, Right);
}

template <typename T, int Row, int Col>
inline TMatrix<T, Row, Col>& operator+=(TMatrix<T, Row, Col>& Left, const T Value)
{
    for(auto i = 0; i < Row*Col; i++)
    {
        Left.Data[i] += Value;
    }
    return Left;
}

template <typename T, int Row, int Col>
inline TMatrix<T, Row, Col>& operator+=(TMatrix<T, Row, Col>& Left, const TMatrix<T, Row, Col>& Right)
{
    for(auto i = 0; i < Row*Col; i++)
    {
        Left.Data[i] += Right.Data[i];
    }
    return Left;
}

template <typename T, int Row, int Col>
inline TMatrix<T, Row, Col>& operator-=(TMatrix<T, Row, Col>& Left, const T Value)
{
    for(auto i = 0; i < Row*Col; i++)
    {
        Left.Data[i] -= Value;
    }
    return Left;
}

template <typename T, int Row, int Col>
inline TMatrix<T, Row, Col>& operator-=(TMatrix<T, Row, Col>& Left, const TMatrix<T, Row, Col>& Right)
{
    for(auto i = 0; i < Row*Col; i++)
    {
        Left.Data[i] -= Right.Data[i];
    }
    return Left;
}

template <typename T, int Row, int Col>
inline TMatrix<T, Row, Col>& operator*=(TMatrix<T, Row, Col>& Left, const T Value)
{
    for(auto i = 0; i < Row*Col; i++)
    {
        Left.Data[i] *= Value;
    }
    return Left;
}

template <typename T, int n>
inline TMatrix<T, n, n>& operator*=(TMatrix<T, n, n>& Left, const TMatrix<T, n, n>& Right)
{
    TMatrix<T, n, n> Result;
    TMatrix<T, n, n> TransposeRight = Transpose(Right);
    const TMatrix<T, n, n> TempLeft = Left;
    for(auto i = 0; i < n; i++)
    {        
        for(auto j = 0; j < n; j++)
        {
            Left.Data[n*i+j] = Dot(TempLeft.Rows[i], TransposeRight.Rows[j]);
        }
    }
    return Left;
}

template <typename T, int Row, int Col>
inline TMatrix<T, Col, Row> Transpose(const TMatrix<T, Row, Col>& Mat)
{
    TMatrix<T, Col, Row> Result;
    for(auto i = 0; i < Row*Col; i++)
    {
        auto j = i/Row;
        auto k = i%Row;
        Result.Data[i] = Mat.Data[Col*k+j];
    }
    return Result;
}

template <typename T, int N>
inline TMatrix<T, N, N> Identity()
{
    return TMatrix<T, N, N>(1);
}

template <typename T, int N>
inline TMatrix<T, N, N> Inverse(const TMatrix<T, N, N>& Mat)
{
    TMatrix<T, N, N> AugmentedMatrix[2];
    AugmentedMatrix[0] = Mat;
    AugmentedMatrix[1] = Identity<T, N>();    
    for(auto j = 0; j < N; j++)
    {

        //NOTE(EVERYONE): Find the highest absolute value where where i > j (rows)
        T HighestValue = 0;
        int Row = 0;        
        for(auto i = 0; i < N; i++)
        {
            if(i >= j)
            {
                T SwapValue = Mat.Data[N*i+j];
                if(Abs(SwapValue) > Abs(HighestValue))
                {
                    HighestValue = SwapValue;
                    Row = i;
                }
            }
        }

        //NOTE(EVERYONE): If no highest value is found. The matrix is singular.
        ASSERT(HighestValue != 0, "The matrix is singular no identity can be found");
        if(HighestValue == 0)
            return AugmentedMatrix[1];
        else
        {
            if(Row != j)
            {
                //NOTE(EVERYONE): Swap the rows
                t_vec<T, N> RowTemp = AugmentedMatrix[0].Rows[Row];                
                AugmentedMatrix[0].Rows[Row] = AugmentedMatrix[0].Rows[j];
                AugmentedMatrix[0].Rows[j] = RowTemp;
                t_vec<T, N> RowTemp2 = AugmentedMatrix[1].Rows[Row];
                AugmentedMatrix[1].Rows[Row] = AugmentedMatrix[1].Rows[j];
                AugmentedMatrix[1].Rows[j] = RowTemp2;
            }

            //NOTE(EVERYONE): Multiply by to get a 1 in the pivot
            const T DivMultiple = AugmentedMatrix[0].Data[N*j+j];
            AugmentedMatrix[0].Rows[j] /= DivMultiple;
            AugmentedMatrix[1].Rows[j] /= DivMultiple;

            for(auto i = 0; i < N; i++)
            {
                if(i != j)
                {
                    //NOTE(EVERYONE): Add to get 0's to the left of the pivot 
                    const T MulMultiple = -AugmentedMatrix[0].Data[N*i+j];
                    AugmentedMatrix[0].Rows[i] += (MulMultiple * AugmentedMatrix[0].Rows[j]);
                    AugmentedMatrix[1].Rows[i] += (MulMultiple * AugmentedMatrix[1].Rows[j]);
                }
            }
        }
    }
    return AugmentedMatrix[1];
}

template <typename T, int Row, int Col>
inline bool operator==(const TMatrix<T, Row, Col>& Left, const TMatrix<T, Row, Col>& Right)
{
    for(auto i = 0; i < Row*Col; i++)
    {
        if(Left.Data[i] == Right.Data[i])
        {
        }
        else
        {
            return false;
        }
    }
    return true;
}

template <typename T>
inline TMatrix<T, 4, 4> ScaleMatrix(const T a, const T b, const T c)
{
    TMatrix<T, 4, 4> Result(1);
    Result[0] = a;
    Result[5] = b;
    Result[10] = c;
    return Result;
}

template <typename T>
inline TMatrix<T, 4, 4> ScaleMatrix(const TVector<T, 3>& ScaleVector)
{
    return ScaleMatrix(ScaleVector.a, ScaleVector.b, ScaleVector.c);
}

template <typename T>
inline TMatrix<T, 4, 4> ScaleMatrix(const T a)
{
    return ScaleMatrix(a, a, a);
}

template <typename T>
inline TMatrix<T, 4, 4> RotateMatrix_Z(const T Angle)
{
    TMatrix<T, 4, 4> Result(1);
    const T c = cos(Angle);
    const T s = sin(Angle);
    
    Result[0] = c;
    Result[1] = -s;
    Result[4] = s;
    Result[5] = c;
    return Result;
}

template <typename T>
inline TMatrix<T, 4, 4> RotateMatrix_X(const T Angle)
{
    TMatrix<T, 4, 4> Result(1);
    const T c = cos(Angle);
    const T s = sin(Angle);

    Result[5] = c;
    Result[6] = -s;
    Result[9] = s;
    Result[10] = c;

    return Result;
}

template <typename T>
inline TMatrix<T, 4, 4> RotateMatrix_Y(const T Angle)
{
    TMatrix<T, 4, 4> Result(1);
    const T c = cos(Angle);
    const T s = sin(Angle);

    Result[0] = c;
    Result[2] = s;
    Result[8] = -s;
    Result[10] = c;
    return Result;
}

template <typename T>
inline TMatrix<T, 4, 4> RotateMatrix(const TVector<T, 3>& Axis, const T Angle)
{
    TMatrix<T, 4, 4> Result(1);
    const T c = cos(Angle);
    const T s = sin(Angle);
    const T cMinus = 1-c;

    const T x = Axis.x;
    const T y = Axis.y;
    const T z = Axis.z;

    Result[0] = c + (cMinus*SQR(x));
    Result[1] = (cMinus*(x*y)) - (s*z);
    Result[2] = (cMinus*(x*z)) + (s*y);
    Result[4] = (cMinus*(x*y)) + (s*z);
    Result[5] = c + (cMinus*SQR(y));
    Result[6] = (cMinus*(y*z)) - (s*x);
    Result[8] = (cMinus*(x*z)) - (s*y);
    Result[9] = (cMinus*(y*z)) + (s*x);
    Result[10] = c + (cMinus*SQR(z));
}

template <typename T>
inline TMatrix<T, 4, 4> TranslateMatrix(const T x, const T y, const T z)
{
    TMatrix<T, 4, 4> Result(1);
    Result[3] = x;
    Result[7] = y;
    Result[11] = z;
    return Result;
}

template <typename T>
inline TMatrix<T, 4, 4> TranslateMatrix(const TVector<T, 3>& TranslateVec)
{
    return TranslateMatrix(TranslateVec.x, TranslateVec.y, TranslateVec.z);
}

/*TODO(JJ): THIS PROJECTION MATRIX IS COMPLETELY F-UP, FIX IT WHEN YOUR FEELING SMART
template <typename T>
inline TMatrix<T, 4, 4> PerspectiveMatrix(const T Left, const T Right, const T Top,
                                       const T Bottom, const T Near, const T Far)
{
    TMatrix<T, 4, 4> Mat(1);

    Mat[0] = (2*Near)/(Right-Left);
    Mat[2] = (Right+Left)/(Right-Left);
    Mat[5] = (2*Near)/(Top-Bottom);
    Mat[6] = (Top+Bottom)/(Top-Bottom);
    Mat[10] = -((Far+Near)/(Far-Near));
    Mat[11] = -((2*Near*Far)/(Far-Near));
    Mat[14] = -1;
    return Mat;

    
template <typename T>
inline TMatrix<T, 4, 4> InfinitePerspectiveMatrix(const T Left, const T Right, const T Top,
                                               const T Bottom, const T Near, const T Far)
{
    TMatrix<T, 4, 4> Mat;

    Mat[0] = (2*Near)/(Right-Left);
    Mat[2] = (Right+Left)/(Right-Left);
    Mat[5] = (2*Near)/(Top-Bottom);
    Mat[6] = (Top+Bottom)/(Top-Bottom);
    Mat[10] = -1;
    Mat[11] = -2*Near;
    Mat[14] = -1;
}

    }*/

    
    
template <typename T>
inline TMatrix<T, 4, 4> PerspectiveMatrix(const T FOV, const T AspectRatio,
                                       const T Near, const T Far)
{
    TMatrix<T, 4, 4> Result(1);

    T q = 1 / tan(TO_RADIAN(0.5f*FOV));
    T a = q / AspectRatio;

    T b = (Near + Far) / (Near - Far);
    T c = (2.0f * Near * Far) / (Near - Far);

    Result[0+0*4] = a;
    Result[1+1*4] = q;
    Result[2+2*4] = b;
    Result[2+3*4] = -1.0;
    Result[3+2*4] = c;
    return Result;
}

template <typename T>
inline TMatrix<T, 4, 4> OrthographicMatrix(const T Left, const T Right, const T Top,
                                        const T Bottom, const T Near, const T Far)
{
    TMatrix<T, 4, 4> Mat(1);

    Mat[0] = 2/(Right-Left);
    Mat[3] = -((Right+Left)/(Right-Left));
    Mat[5] = 2/(Top-Bottom);
    Mat[7] = -((Top+Bottom)/(Top-Bottom));
    Mat[10] = -2/(Far-Near);
    Mat[11] = -((Far+Near)/(Far-Near));
}

template <typename T>
inline TMatrix<T, 4, 4> ToMatrix(const TQuaternion<T>& quat)
{
    const T x2 = SQR(quat.x);
    const T y2 = SQR(quat.y);
    const T z2 = SQR(quat.z);
    const T x = quat.x;
    const T y = quat.y;
    const T z = quat.z;
    const T w = quat.w;

    TMatrix<T, 4, 4> Result(1);

    Result[0] = 1-(2*y2)-(2*z2); Result[1] = (2*x*y)-(2*w*z); Result[2]  = (2*x*z)+(2*w*y);
    Result[4] = (2*x*y)+(2*w*z); Result[5] = 1-(2*x2)-(2*z2); Result[6]  = (2*y*z)-(2*w*x);
    Result[8] = (2*x*z)-(2*w*y); Result[9] = (2*y*z)+(2*w*x); Result[10] = 1-(2*x2)-(2*y2);
    return Result;
}

template <typename T>
inline TMatrix<T, 4, 4> LookAt(const TVector<T, 3>& Position, const TVector<T, 3>& Target,
                            const TVector<T, 3>& Up)
{
    TMatrix<T, 4, 4> Result(1);
    auto f = Norm(Target-Position);
    auto s = Cross(f, Norm(Up));
    auto u = Cross(s, f);

    Result[0] = s.x;
    Result[4] = s.y;
    Result[8] = s.z;

    Result[1] = u.x;
    Result[5] = u.y;
    Result[9] = u.z;

    Result[2] = -f.x;
    Result[6] = -f.y;
    Result[10] = -f.z;

    return Result * TranslateMatrix(-Position);
}

template <typename T>
inline TMatrix<T, 3, 3> ToMat3x3(const TMatrix<T, 4, 4>& mat)
{
    TMatrix<T, 3, 3> Result;
    for(auto i = 0; i < 3; i++)
    {
        Result.Rows[i] = TVector<T, 3>(mat.Rows[i].x, mat.Rows[i].y, mat.Rows[i].z);
    }
    return Result;
}

typedef TMatrix<int, 2, 2> FMatrix2i;
typedef TMatrix<int, 3, 3> FMatrix3i;
typedef TMatrix<int, 4, 4> FMatrix4i;

typedef TMatrix<float, 2, 2> FMatrix2f;
typedef TMatrix<float, 3, 3> FMatrix3f;
typedef TMatrix<float, 4, 4> FMatrix4f;

typedef TMatrix<double, 2, 2> FMatrix2d;
typedef TMatrix<double, 3, 3> FMatrix3d;
typedef TMatrix<double, 4, 4> FMatrix4d;

#define MAT_H
#endif
