#if !defined(WIDGET_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <ObjectFramework/ObjectFramework.h>
#include <Interfaces/Managers/IMemoryManager.h>
#include <Interfaces/Managers/IPlatformManager.h>
#include <Utility/Logger.h>

static IMemoryManager* gMemoryManager;
static FILE* WIDGET_CHANNEL_File;
FLogger* gLogger = nullptr;

#include "WidgetTask.h"
#include "WidgetObject.h"
#include "WidgetScene.h"

class Widget : public IWidget
{
private:
protected:
public:

    Widget();
    IWidgetScene* CreateScene() final;
    void DestroyScene(IWidgetScene** Scene) final;
    ~Widget();
};


#define WIDGET_H
#endif
