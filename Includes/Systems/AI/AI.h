#if !defined(AI_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <ObjectFramework/ObjectFramework.h>
#include <Interfaces/Managers/IMemoryManager.h>

static IMemoryManager* gMemoryManager;

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
