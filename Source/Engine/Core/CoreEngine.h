#if !defined(COREENGINE_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <AtomicTypes.h>
#include <Macro.h>
#include <Assert.h>
#include <Libs.h>
#include <Events.h>
#include <Logger.h>
#include "Managers/Public/EnvironmentManager.h"
#include "Managers/Public/PlatformManager.h"
#include "Managers/Public/TaskManager.h"
#include "Managers/Public/StateManager.h"
#include "Managers/Public/ServiceManager.h"
#include "Framework/Public/Scheduler.h"

class FCoreEngine
{
private:
    IWindow* m_MainWindow;
    FScheduler m_Scheduler;
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
