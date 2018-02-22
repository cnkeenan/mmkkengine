/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <Systems/Physics/Physics.h>

#include "PhysicsTask.cpp"
#include "PhysicsObject.cpp"
#include "PhysicsScene.cpp"

Physics::Physics()
{
}

IPhysicsScene* Physics::CreateScene()
{
    IPhysicsScene* Result = new PhysicsScene();
    return Result;
}

void Physics::DestroyScene(IPhysicsScene** Scene)
{
    if((*Scene))
    {
        PhysicsScene** RealScene = (PhysicsScene**)Scene;
        delete (*RealScene);
        (*Scene) = nullptr;
    }
}

Physics::~Physics()
{
}

extern "C"
{
    EXPORT IPhysics* CreatePhysicsSystem(FLogger* Logger, IMemoryManager* MemoryManager)
    {
        PHYSICS_CHANNEL_File = fopen(PHYSICS_CHANNEL_PATH, "w");
        gMemoryManager = MemoryManager;
        gLogger = Logger;
        IPhysics* Result = new Physics();
        return Result;
    }

    EXPORT void DestroyPhysicsSystem(IPhysics** System)
    {
        if((*System))
        {
            delete (*System);
            (*System) = nullptr;
        }
        gLogger = nullptr;
        gMemoryManager = nullptr;
        fclose(PHYSICS_CHANNEL_File);
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
