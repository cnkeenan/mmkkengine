/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <Systems/Input/Input.h>

#include "InputTask.cpp"
#include "InputObject.cpp"
#include "InputScene.cpp"

Input::Input()
{
}

IInputScene* Input::CreateScene()
{
    IInputScene* Result = new InputScene();
    return Result;
}

void Input::DestroyScene(IInputScene** Scene)
{
    if((*Scene))
    {
        InputScene** RealScene = (InputScene**)Scene;
        delete (*RealScene);
        (*Scene) = nullptr;
    }
}

Input::~Input()
{
}

extern "C"
{
    EXPORT IInput* CreateInputSystem(FLogger* Logger, IMemoryManager* MemoryManager)
    {
        INPUT_CHANNEL_File = fopen(INPUT_CHANNEL_PATH, "w");
        gMemoryManager = MemoryManager;
        gLogger = Logger;
        IInput* Result = new Input();
        return Result;        
    }

    EXPORT void DestroyInputSystem(IInput** System)
    {
        if((*System))
        {
            delete (*System);
            (*System) = nullptr;
        }
        gLogger = nullptr;
        gMemoryManager = nullptr;
        fclose(INPUT_CHANNEL_File);
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
