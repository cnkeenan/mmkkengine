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
    EXPORT IPhysics* CreatePhysicsSystem(IMemoryManager* MemoryManager)
    {
        gMemoryManager = MemoryManager;
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
        gMemoryManager = nullptr;
    }
}
