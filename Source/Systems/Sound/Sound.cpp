/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <Systems/Sound/Sound.h>

#include "SoundTask.cpp"
#include "SoundObject.cpp"
#include "SoundScene.cpp"

Sound::Sound()
{
}

ISoundScene* Sound::CreateScene()
{
    ISoundScene* Result = new SoundScene();
    return Result;
}

void Sound::DestroyScene(ISoundScene** Scene)
{
    if((*Scene))
    {
        SoundScene** RealScene = (SoundScene**)Scene;
        delete (*RealScene);
        (*Scene) = nullptr;
    }
}

Sound::~Sound()
{
}

extern "C"
{
    EXPORT ISound* CreateSoundSystem(IMemoryManager* MemoryManager)
    {
        gMemoryManager = MemoryManager;
        ISound* Result = new Sound();
        return Result;
    }

    EXPORT void DestroySoundSystem(ISound** System)
    {
        if((*System))
        {
            delete (*System);
            (*System) = nullptr;
        }
        gMemoryManager = nullptr;
    }
}
