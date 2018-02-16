#if !defined(TRANSFORM_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <ObjectFramework/ObjectFramework.h>
#include <Interfaces/Managers/IMemoryManager.h>

static IMemoryManager* gMemoryManager = nullptr;

#include "TransformTask.h"
#include "TransformObject.h"
#include "TransformScene.h"

class Transform : public ITransform
{
private:
protected:
public:

    Transform();
    ITransformScene* CreateScene() final;
    void DestroyScene(ITransformScene** Scene) final;
    ~Transform();
};

#define TRANSFORM_H
#endif
