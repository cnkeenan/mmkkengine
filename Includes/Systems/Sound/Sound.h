#if !defined(SOUND_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <ObjectFramework/ObjectFramework.h>
#include <Interfaces/Managers/IMemoryManager.h>
#include <Interfaces/Managers/IPlatformManager.h>
#include <Utility/Logger.h>

static IMemoryManager* gMemoryManager;
static FILE* SOUND_CHANNEL_File;
FLogger* gLogger = nullptr;

#include "SoundTask.h"
#include "SoundObject.h"
#include "SoundScene.h"

class Sound : public ISound
{
private:
protected:
public:

    Sound();
    ISoundScene* CreateScene() final;
    void DestroyScene(ISoundScene** Scene) final;
    ~Sound();
};

#define SOUND_H
#endif
