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
    EXPORT IAI* CreateAISystem(FLogger* Logger, IMemoryManager* MemoryManager)
    {
        AI_CHANNEL_File = fopen(AI_CHANNEL_PATH, "w");
        gMemoryManager = MemoryManager;
        gLogger = Logger;
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
        gLogger = nullptr;
        gMemoryManager = nullptr;
        fclose(AI_CHANNEL_File);
    }
}

void* operator new(ptr_size Size)
{
    return gMemoryManager->Allocate(Size);
}

void* operator new[](ptr_size Size)
{
    return gMemoryManager->Allocate(Size);
}

void operator delete(void* Pointer)
{
    gMemoryManager->Free(Pointer);
}

void operator delete[](void* Pointer)
{
    gMemoryManager->Free(Pointer);
}
