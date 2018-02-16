#if !defined(INPUT_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <ObjectFramework/ObjectFramework.h>
#include <Interfaces/Managers/IMemoryManager.h>

static IMemoryManager* gMemoryManager;

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
