/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <Systems/Collision/Collision.h>

#include "CollisionTask.cpp"
#include "CollisionObject.cpp"
#include "CollisionScene.cpp"

Collision::Collision()
{
}

ICollisionScene* Collision::CreateScene()
{
    ICollisionScene* Result = new CollisionScene();
    return Result;
}

void Collision::DestroyScene(ICollisionScene** Scene)
{
    if((*Scene))
    {
        CollisionScene** RealScene = (CollisionScene**)Scene;
        delete (*RealScene);
        (*Scene) = nullptr;
    }
}

Collision::~Collision()
{
}

extern "C"
{
    EXPORT ICollision* CreateCollisionSystem(FLogger* Logger, IMemoryManager* MemoryManager)
    {
        COLLISION_CHANNEL_File = fopen(COLLISION_CHANNEL_PATH, "w");
        gMemoryManager = MemoryManager;
        gLogger = Logger;
        ICollision* Result = new Collision();
        return Result;
    }

    EXPORT void DestroyCollisionSystem(ICollision** System)
    {
        if((*System))
        {
            delete (*System);
            (*System) = nullptr;
        }
        gLogger = nullptr;
        gMemoryManager = nullptr;
        fclose(COLLISION_CHANNEL_File);
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
