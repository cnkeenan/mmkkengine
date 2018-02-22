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
    EXPORT ISound* CreateSoundSystem(FLogger* Logger, IMemoryManager* MemoryManager)
    {
        SOUND_CHANNEL_File = fopen(SOUND_CHANNEL_PATH, "w");
        gMemoryManager = MemoryManager;
        gLogger = Logger;
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
        gLogger = nullptr;            
        gMemoryManager = nullptr;
        fclose(SOUND_CHANNEL_File);
    }
}

void* operator new(ptr_size Size)
{
    return gMemoryManager->Allocate(Size);
}

void* operator new[](ptr_size Size)
{
    return gMemoryManager->Allocate(Size);
}

void operator delete(void* Pointer)
{
    gMemoryManager->Free(Pointer);
}

void operator delete[](void* Pointer)
{
    gMemoryManager->Free(Pointer);
}
