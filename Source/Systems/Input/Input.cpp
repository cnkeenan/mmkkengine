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
    EXPORT IInput* CreateInputSystem(IMemoryManager* MemoryManager)
    {
        gMemoryManager = MemoryManager;
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
        gMemoryManager = nullptr;
    }
}
