#if !defined(WIDGET_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <ObjectFramework/ObjectFramework.h>
#include <Interfaces/Managers/IMemoryManager.h>

static IMemoryManager* gMemoryManager;

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
