/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <Systems/Transform/Transform.h>

#include "TransformTask.cpp"
#include "TransformObject.cpp"
#include "TransformScene.cpp"

Transform::Transform()
{
}

ITransformScene* Transform::CreateScene()
{
    ITransformScene* Result = new TransformScene();
    return Result;
}

void Transform::DestroyScene(ITransformScene** Scene)
{
    if((*Scene))
    {
        TransformScene** RealScene = (TransformScene**)Scene;
        delete (*RealScene);
        (*Scene) = nullptr;
    }
}

Transform::~Transform()
{
}

extern "C"
{
    EXPORT ITransform* CreateTransformSystem(IMemoryManager* MemoryManager)
    {
        gMemoryManager = MemoryManager;
        ITransform* Result = new Transform();
        return Result;
    }

    EXPORT void DestroyTransformSystem(ITransform** System)
    {
        if((*System))
        {
            delete (*System);
            (*System) = nullptr;
        }
        gMemoryManager = nullptr;
    }
}
