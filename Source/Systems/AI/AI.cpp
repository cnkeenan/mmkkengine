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

void AI::DestroyScene(IAIScene** Scene)
{
    if((*Scene))
    {
        AIScene** RealScene = (AIScene**)Scene;
        delete (*RealScene);
        (*Scene) = nullptr;
    }
}

AI::~AI()
{
}

extern "C"
{
    EXPORT IAI* CreateAISystem(IMemoryManager* MemoryManager)
    {
        gMemoryManager = MemoryManager;
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
        gMemoryManager = nullptr;
    }
}

