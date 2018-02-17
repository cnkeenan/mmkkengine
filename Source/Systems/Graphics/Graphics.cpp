/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <Systems/Graphics/Graphics.h>

#include "GraphicsTask.cpp"
#include "GraphicsObject.cpp"
#include "GraphicsScene.cpp"

Graphics::Graphics()
{
    gPlatformManager->InitializeOpenGLContext(gWindow);
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
    EXPORT IGraphics* CreateGraphicsSystem(IMemoryManager* MemoryManager,
                                           IPlatformManager* PlatformManager,
                                           IWindow* Window)
    {
        gMemoryManager = MemoryManager;
        gPlatformManager = PlatformManager;
        gWindow = Window;
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
        gPlatformManager = nullptr;
        gWindow = nullptr;
    }
}
