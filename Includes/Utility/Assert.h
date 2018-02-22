#if !defined(ASSERT_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include "Logger.h"

#if DEBUG_BUILD
#define ASSERT(x)                               \
    do                                          \
    {                                           \
        if(!(x))                                \
        {                                       \
            INVALID_CODE_PATH;                  \
        }                                       \
    } while(0)
#else
#define ASSERT(x, y)
#endif

#define ASSERT_H
#endif
