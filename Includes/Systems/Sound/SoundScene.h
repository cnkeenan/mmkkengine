#if !defined(SOUNDSCENE_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class SoundScene : public ISoundScene
{
private:
    SoundTask m_Task;

    static const ptr_size NUMBER_OF_OBJECTS=64;
    FPool* m_ObjectPool;

protected:
public:

    SoundScene();
        
    ISoundObject* CreateObject() final;
    void DestroyObject(ISoundObject* Object) final;        
        
    void BeginPlay() final;
    void Tick(float DeltaTime) final;
    ITask* GetTask() final;
    
    ~SoundScene();
};

#define SOUNDSCENE_H
#endif
