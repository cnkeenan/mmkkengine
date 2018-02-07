#if !defined(MATHCOMMON_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <math.h>
#define SQR(x) x*x
#define PI 3.14159265359f
#define TO_RADIAN(x) (x * 180.0f / PI)

template <typename T>
inline T Abs(const T Value)
{
    if(Value < 0)
        return -Value;
    else
        return Value;
}


#define MATHCOMMON_H
#endif
