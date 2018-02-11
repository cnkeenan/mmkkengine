#if !defined(ATOMICTYPES_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#if OS_LINUX
#include <stddef.h>
#endif
#include <stdint.h>

typedef uint8_t uint8;
typedef int8_t int8;

typedef uint16_t uint16;
typedef int16_t int16;

typedef uint32_t uint32;
typedef int32_t int32;

typedef uint64_t uint64;
typedef int64_t int64;

//NOTE(EVERYONE): 8 bytes on 64 bit architectures, 4 bytes on 32 bit
typedef size_t ptr_size;

#define ATOMICTYPES_H
#endif
