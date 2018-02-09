#if !defined(COREENGINE_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <AtomicTypes.h>
#include <Assert.h>
#include <Libs.h>
#include "Managers/Public/PlatformManager.h"
#include "Managers/Public/TaskManager.h"

class FCoreEngine
{
private:
    IWindow* m_MainWindow;
    
public:
    void Initialize();
    void Tick();
    void Destroy();

    int Foo()
    {
        return 2;
    }
};

#define COREENGINE_H
#endif
