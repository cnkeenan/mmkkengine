#if !defined(ISOUND_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
class ISound : public ISystem
{
private:
protected:
public:

    virtual ISoundScene* CreateScene() = 0;
    virtual void DestroyScene(ISoundScene** Scene) = 0;
    ESystemType GetType() final { return ESystemType::SOUND; }
    virtual ~ISound() {}
};


//NOTE(EVERYONE): If we need managers add them here
typedef ISound* fp_CreateSoundSystem(class FLogger* Logger, class IMemoryManager* MemoryManager);
typedef void fp_DestroySoundSystem(ISound** System);


#define ISOUND_H
#endif
