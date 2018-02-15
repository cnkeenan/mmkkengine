/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <Systems/AI/AI.h>

#include "AITask.cpp"
#include "AIObject.cpp"
#include "AIScene.cpp"

AI::AI()
{
}

IAIScene* AI::CreateScene()
{
    IAIScene* Result = new AIScene();

    return Result;
}

AI::~AI()
{
}

EXPORT IAI* CreateAISystem()
{
    IAI* Result = new AI();
    return Result;
}

EXPORT void DestroyAISystem(IAI** System)
{
    if((*System))
    {
        delete (*System);
        (*System) = nullptr;
    }
}

