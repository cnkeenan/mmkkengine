#if !defined(COLLISIONOBJECT_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class CollisionObject : public ICollisionObject
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

    void* operator new(size_t Size);
    void operator delete(void* Object);
    
    ~CollisionObject() {}
};

#define COLLISIONOBJECT_H
#endif
