/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <Systems/Widget/Widget.h>

#include "WidgetTask.cpp"
#include "WidgetObject.cpp"
#include "WidgetScene.cpp"

Widget::Widget()
{
}

IWidgetScene* Widget::CreateScene()
{
    IWidgetScene* Result = new WidgetScene();
    return Result;
}

void Widget::DestroyScene(IWidgetScene** Scene)
{
    if((*Scene))
    {
        WidgetScene** RealScene = (WidgetScene**)Scene;
        delete (*RealScene);
        (*Scene) = nullptr;
    }
}

Widget::~Widget()
{
}

extern "C"
{
    EXPORT IWidget* CreateWidgetSystem(FLogger* Logger, IMemoryManager* MemoryManager)
    {
        WIDGET_CHANNEL_File = fopen(WIDGET_CHANNEL_PATH, "w");
        gLogger = Logger;
        gMemoryManager = MemoryManager;
        IWidget* Result = new Widget();
        return Result;
    }

    EXPORT void DestroyWidgetSystem(IWidget** System)
    {
        if((*System))
        {
            delete (*System);
            (*System) = nullptr;
            gLogger = nullptr;
            gMemoryManager = nullptr;
            fclose(WIDGET_CHANNEL_File);
        }
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
