#if !defined(COLLISIONSCENE_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class CollisionScene : public ICollisionScene
{
    
private:
    CollisionTask m_Task;

    static const ptr_size NUMBER_OF_OBJECTS = 64;
    TObjectPool<CollisionObject> m_ObjectPool;
protected:
public:

    CollisionScene();
        
    ICollisionObject* CreateObject() final;
    void DestroyObject(ICollisionObject* Object) final;        
        
    void BeginPlay() final;
    void Tick(float DeltaTime) final;
    ITask* GetTask() final;
    
    ~CollisionScene();
};

#define COLLISIONSCENE_H
#endif
