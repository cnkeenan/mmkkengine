/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <Systems/Graphics/Graphics.h>

#include "GraphicsTask.cpp"
#include "GraphicsObject.cpp"
#include "GraphicsScene.cpp"

Graphics::Graphics()
{
}

IGraphicsScene* Graphics::CreateScene()
{
    IGraphicsScene* Result = new GraphicsScene();
    return Result;
}

void Graphics::DestroyScene(IGraphicsScene** Scene)
{
    if((*Scene))
    {
        GraphicsScene** RealScene = (GraphicsScene**)Scene;
        delete (*RealScene);
        (*Scene) = nullptr;
    }
}

Graphics::~Graphics()
{
}

extern "C"
{
    EXPORT IGraphics* CreateGraphicsSystem(IMemoryManager* MemoryManager)
    {
        gMemoryManager = MemoryManager;
        IGraphics* Result = new Graphics();
        return Result;
    }

    EXPORT void DestroyGraphicsSystem(IGraphics** System)
    {        
        if((*System))
        {
            delete (*System);
            (*System) = nullptr;
        }
        gMemoryManager = nullptr;
    }
}
