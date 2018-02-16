#if !defined(PHYSICS_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <ObjectFramework/ObjectFramework.h>
#include <Interfaces/Managers/IMemoryManager.h>

static IMemoryManager* gMemoryManager;

#include "PhysicsTask.h"
#include "PhysicsObject.h"
#include "PhysicsScene.h"

class Physics : public IPhysics
{
private:
protected:
public:

    Physics();
    IPhysicsScene* CreateScene() final;
    void DestroyScene(IPhysicsScene** Scene) final;
    ~Physics();
};

#define PHYSICS_H
#endif
