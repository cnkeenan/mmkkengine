#if !defined(PLATFORMDETECTION_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

//NOTE(EVERYONE): Got all my info at https://sourceforge.net/p/predef/wiki/Home/
//TODO(EVERYONE): This needs some hard testing
//TODO(EVERYONE): Still need to do processor architecture
//TODO(EVERYONE): Also compilers if we want to develop on more than msvc and gcc


#if !defined(OS_WINDOWS)
#define OS_WINDOWS 0
#endif

#if !defined(OS_MAC)
#define OS_MAC 0
#endif

#if !defined(OS_LINUX)
#define OS_LINUX 0
#endif

#if defined(_WIN32)
#undef OS_WINDOWS
#define OS_WINDOWS 1
#endif

#if defined(__APPLE__) && defined(__MACH__)
#undef OS_MAC
#define OS_MAC 1
#endif

#if defined(__linux__)
#undef OS_LINUX
#define OS_LINUX 1
#endif

#define PLATFORMDETECTION_H
#endif
