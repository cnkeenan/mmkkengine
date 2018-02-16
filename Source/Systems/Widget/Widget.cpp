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
    EXPORT IWidget* CreateWidgetSystem(IMemoryManager* MemoryManager)
    {
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
            gMemoryManager = nullptr;
        }
    }
}
