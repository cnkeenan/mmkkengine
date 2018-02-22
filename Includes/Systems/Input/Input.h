#if !defined(INPUT_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <ObjectFramework/ObjectFramework.h>
#include <Interfaces/Managers/IMemoryManager.h>
#include <Interfaces/Managers/IPlatformManager.h>
#include <Utility/Logger.h>

static IMemoryManager* gMemoryManager;
static FILE* INPUT_CHANNEL_File;
FLogger* gLogger = nullptr;

#include "InputTask.h"
#include "InputObject.h"
#include "InputScene.h"

class Input : public IInput
{
private:
protected:
public:

    Input();
    IInputScene* CreateScene() final;
    void DestroyScene(IInputScene** Scene) final;
    ~Input();
};

#define INPUT_H
#endif
