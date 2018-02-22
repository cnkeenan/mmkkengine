#if !defined(AI_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <ObjectFramework/ObjectFramework.h>
#include <Interfaces/Managers/IMemoryManager.h>
#include <Interfaces/Managers/IPlatformManager.h>
#include <Utility/Logger.h>

static IMemoryManager* gMemoryManager;
static FILE* AI_CHANNEL_File;
FLogger* gLogger = nullptr;

#include "AITask.h"
#include "AIObject.h"
#include "AIScene.h"

class AI : public IAI
{
private:
protected:
public:

    AI();
    IAIScene* CreateScene() final;
    void DestroyScene(IAIScene** Scene) final;
    ~AI(); 
};

#define AI_H
#endif
