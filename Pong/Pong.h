#if !defined(PONG_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <ObjectFramework/ObjectFramework.h>


#ifdef GAME_EXPORT
#define PONG_API EXPORT
#else
#define PONG_API IMPORT
#endif

#include "UBall.h"
#include "UPlayerPaddle.h"
#include "UAIPaddle.h"

#define PONG_H
#endif
