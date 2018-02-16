#if !defined(COLLISION_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <ObjectFramework/ObjectFramework.h>
#include <Interfaces/Managers/IMemoryManager.h>

static IMemoryManager* gMemoryManager;

#include "CollisionTask.h"
#include "CollisionObject.h"
#include "CollisionScene.h"

class Collision : public ICollision
{
private:
protected:
public:

    Collision();
    ICollisionScene* CreateScene() final;
    void DestroyScene(ICollisionScene** Scene) final;
    ~Collision();
};

#define COLLISION_H
#endif
