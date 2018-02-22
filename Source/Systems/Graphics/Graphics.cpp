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
    EXPORT IGraphics* CreateGraphicsSystem(FLogger* Logger, IMemoryManager* MemoryManager,
                                           IPlatformManager* PlatformManager,
                                           IWindow* Window)
    {
        GRAPHICS_CHANNEL_File = fopen(GRAPHICS_CHANNEL_PATH, "w");
        gMemoryManager = MemoryManager;
        gPlatformManager = PlatformManager;
        gWindow = Window;
        gLogger = Logger;
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
        gLogger = nullptr;
        fclose(GRAPHICS_CHANNEL_File);
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
