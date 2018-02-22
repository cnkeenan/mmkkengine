#if !defined(SOUNDOBJECT_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class SoundObject : public ISoundObject
{
private:
    bool m_IsInitialized;
protected:
public:

    void Create();
    void Destroy();
    
    void BeginPlay() final;
    void Tick(float DeltaTime) final;
    bool IsInitialized() final;
    void* operator new(size_t Size, void* Pointer);
    void operator delete(void* Object, void* Pointer);
    ~SoundObject() {}
};

#define SOUNDOBJECT_H
#endif
