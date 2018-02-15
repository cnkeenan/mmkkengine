#if !defined(AI_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <ObjectFramework/ObjectFramework.h>

#include "AITask.h"
#include "AIScene.h"
#include "AIObject.h"

class AI : public IAI
{
private:
protected:
public:

    AI();
    IAIScene* CreateScene() final;    
    ~AI(); 
};

#define AI_H
#endif
