#if !defined(COREENGINE_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <ObjectFramework/ObjectFramework.h>
#include <Interfaces/Managers/IPlatformManager.h>
#include <Utility/Delegate.h>
#include <Utility/Logger.h>
#include <Utility/Assert.h>
#include <Utility/Events.h>
#include <Utility/Strings.h>

#include <Engine/Managers/EnvironmentManager.h>
#include <Engine/Managers/PlatformManager.h>
#include <Engine/Managers/TaskManager.h>
#include <Engine/Managers/StateManager.h>
#include <Engine/Managers/ServiceManager.h>
#include <Engine/Framework/Scheduler.h>
#include <Engine/Framework/Loader.h>

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

    bool TestEventMethod(TestEvent* Event);
    
};

#define COREENGINE_H
#endif
