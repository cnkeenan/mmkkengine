#if !defined(MACRO_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

#define ARRAYCOUNT(x) (sizeof(x) / sizeof((x)[0]))
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define ABS(x) ((x<0) ? -(x) : (x))
#define BIT(x) (1 << x)
#define SET_BIT(number, x) (number |= 1UL << x)
#define CLEAR_BIT(number, x) (number &= ~(1UL << x))
#define TOGGLE_BIT(number, x) (number ^= 1UL << x)
#define CHECK_BIT(number, x) ((number >> x) & 1UL)
#define SET_BIT_64(number, x) (number |= 1ULL << x)
#define CLEAR_BIT_64(number, x) (number &= ~(1ULL << x))
#define TOGGLE_BIT_64(number, x) (number ^= 1ULL << x)
#define CHECK_BIT_64(number, x) ((number >> x) & 1ULL)
#define INVALID_CODE_PATH *(int*)0 = 0
#define KILOBYTE(x) (x*1024LL)
#define MEGABYTE(x) (x*1024LL*1024LL)
#define GIGABYTE(x) (x*1024LL*1024LL*1024LL)
#define TERABYTE(x) (x*1024LL*1024LL*1024LL*1024LL)

//NOTE(EVERYONE): If you guys are getting errors of these macros being defined multiple times just #undef them.
//Posix defines these in a specific file but not windows 
#define STDIN_FILENO
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#define MACRO_H
#endif
