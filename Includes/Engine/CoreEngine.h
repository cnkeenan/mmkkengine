#if !defined(COREENGINE_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <ObjectFramework/ObjectFramework.h>
#include <Interfaces/Managers/IPlatformManager.h>
#include <Utility/Logger.h>
#include <Utility/Assert.h>
#include <Utility/Events.h>
#include <Utility/Strings.h>
#include <Utility/OpenGL.h>

#include <Engine/Managers/MemoryManager.h>
#include <Engine/Managers/EnvironmentManager.h>
#include <Engine/Managers/PlatformManager.h>
#include <Engine/Managers/TaskManager.h>
#include <Engine/Managers/StateManager.h>
#include <Engine/Managers/ServiceManager.h>
#include <Engine/Framework/Scheduler.h>
#include <Engine/Framework/Loader.h>

static FILE* ENGINE_CHANNEL_File;
static FILE* PLATFORM_CHANNEL_File;

class FCoreEngine
{
private:
    IWindow* m_MainWindow;
    FScheduler m_Scheduler;
    FLoader m_Loader;
    //TODO(EVERYONE): Move this into environment manager
    uint32 m_FPS;
    
    
public:
    void Initialize();
    void Tick();
    void Destroy();
 
};

#define COREENGINE_H
#endif
