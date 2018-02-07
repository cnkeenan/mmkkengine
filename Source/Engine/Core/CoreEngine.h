#if !defined(COREENGINE_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <AtomicTypes.h>
#include <Assert.h>
#include "Managers/Public/PlatformManager.h"

class FCoreEngine
{
private:
    IWindow* m_MainWindow;
    
public:
    void Initialize();
    void Tick();
    void Destroy();
};

#define COREENGINE_H
#endif
