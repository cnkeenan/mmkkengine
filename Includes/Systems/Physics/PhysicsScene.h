#if !defined(PHYSICSSCENE_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class PhysicsScene : public IPhysicsScene
{
private:
    PhysicsTask m_Task;

    static const ptr_size NUMBER_OF_OBJECTS=64;
    TObjectPool<PhysicsObject> m_ObjectPool;

protected:
public:

    PhysicsScene();
        
    IPhysicsObject* CreateObject() final;
    void DestroyObject(IPhysicsObject* Object) final;        
        
    void BeginPlay() final;
    void Tick(float DeltaTime) final;
    ITask* GetTask() final;
    
    ~PhysicsScene();
};

#define PHYSICSSCENE_H
#endif
