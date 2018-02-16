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
    EXPORT ICollision* CreateCollisionSystem(IMemoryManager* MemoryManager)
    {
        gMemoryManager = MemoryManager;
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
        gMemoryManager = nullptr;
    }
}
