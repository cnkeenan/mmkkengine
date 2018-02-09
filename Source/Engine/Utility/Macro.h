#if !defined(MACRO_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

#define ARRAYCOUNT(x) (sizeof(x) / sizeof((x)[0]))
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define ABS(x) ((x<0) ? -(x) : (x))

#define MACRO_H
#endif
