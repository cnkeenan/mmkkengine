#if !defined(GRAPHICS_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <ObjectFramework/ObjectFramework.h>
#include <Interfaces/Managers/IMemoryManager.h>
#include <Interfaces/Managers/IPlatformManager.h>
#include <Utility/OpenGL.h>
#include <Utility/Logger.h>

static IMemoryManager* gMemoryManager;
static IPlatformManager* gPlatformManager;
static IWindow* gWindow;
static FILE* GRAPHICS_CHANNEL_File;
FLogger* gLogger = nullptr;

#include "GraphicsTask.h"
#include "GraphicsObject.h"
#include "GraphicsScene.h"

class Graphics : public IGraphics
{
private:
protected:
public:

    Graphics();
    IGraphicsScene* CreateScene() final;
    void DestroyScene(IGraphicsScene** Scene) final;
    ~Graphics();
};

#define GRAPHICS_H
#endif
