#if !defined(PONG_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <ObjectFramework/ObjectFramework.h>

#if MSVC_COMPILER
#ifdef GAME_EXPORT
#define PONG_API __declspec(dllexport)
#else
#define PONG_API __declspec(dllimport)
#endif
#elif GCC_COMPILER //NOTE(EVERYONE): This might be the same for clang
#ifdef GAME_EXPORT
#define PONG_API __attribute__((visibility("default")))
#else
#define PONG_API
#endif
#endif

#include "UBall.h"
#include "UPlayerPaddle.h"
#include "UAIPaddle.h"

#define PONG_H
#endif
