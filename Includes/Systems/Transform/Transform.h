#if !defined(TRANSFORM_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <ObjectFramework/ObjectFramework.h>
#include <Interfaces/Managers/IMemoryManager.h>
#include <Interfaces/Managers/IPlatformManager.h>
#include <Utility/Logger.h>

static IMemoryManager* gMemoryManager = nullptr;
static FILE* TRANSFORM_CHANNEL_File;
FLogger* gLogger = nullptr;

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
