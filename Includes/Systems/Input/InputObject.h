#if !defined(INPUTOBJECT_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class InputObject : public IInputObject
{
private:
    bool m_IsInitialized;
protected:
public:

    void Create();
    void Destroy();

    
    void* operator new(size_t Size);
    void operator delete(void* Object);
    
    void BeginPlay() final;
    void Tick(float DeltaTime) final;
    bool IsInitialized() final;
    
    ~InputObject() {}
};

#define INPUTOBJECT_H
#endif
