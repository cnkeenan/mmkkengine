#if !defined(TRANSFORMOBJECT_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class TransformObject : public ITransformObject
{
private:
    bool m_IsInitialized;
protected:
public:

    TransformObject() : m_IsInitialized(false) {}                        
    
    void Create();
    void Destroy();
    
    void BeginPlay() final;
    void Tick(float DeltaTime) final;
    bool IsInitialized() final;

    void* operator new(size_t Size);
    void operator delete(void* Object);
    
    ~TransformObject() {}
};

#define TRANSFORMOBJECT_H
#endif
