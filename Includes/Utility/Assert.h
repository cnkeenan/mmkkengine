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
            LOG(FAILURE, RESERVED_CHANNEL, y);  \
            INVALID_CODE_PATH;                  \
        }                                       \
    } while(0)
#else
#define ASSERT(x, y)
#endif

#define ASSERT_H
#endif
