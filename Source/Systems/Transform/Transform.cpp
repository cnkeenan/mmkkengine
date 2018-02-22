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
    EXPORT ITransform* CreateTransformSystem(FLogger* Logger, IMemoryManager* MemoryManager)
    {
        TRANSFORM_CHANNEL_File = fopen(TRANSFORM_CHANNEL_PATH, "w");
        gMemoryManager = MemoryManager;
        gLogger = Logger;
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
        gLogger = nullptr;
        gMemoryManager = nullptr;
        fclose(TRANSFORM_CHANNEL_File);
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
