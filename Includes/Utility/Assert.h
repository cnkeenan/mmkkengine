#if !defined(ASSERT_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

#if DEBUG_BUILD
#define ASSERT(x) if(!(x)) *(int*)0 = 0
#else
#define ASSERT(x)
#endif

#define ASSERT_H
#endif
