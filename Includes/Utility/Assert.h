#if !defined(ASSERT_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include "Logger.h"

#if DEBUG_BUILD
#define ASSERT(x, y)                            \
    do                                          \
    {                                           \
        if(!(x))                                \
        {                                       \
            LOG(FAILURE, y);                    \
            *(int*)0 = 0;                       \
        }                                       \
    } while(0)
#else
#define ASSERT(x, y)
#endif

#define ASSERT_H
#endif
