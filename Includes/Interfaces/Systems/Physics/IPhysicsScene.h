#if !defined(IPHYSICSSCENE_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class IPhysicsScene : public IScene
{
private:
protected:
public:
                    
    virtual IPhysicsObject* CreateObject() = 0;
    virtual void DestroyObject(IPhysicsObject** Object) = 0;                
    
    ESystemType GetType() final { return ESystemType::PHYSICS; }
    virtual void BeginPlay() = 0;
    virtual void Tick(float DeltaTime) = 0;
    virtual ITask* GetTask() = 0;
    
    virtual ~IPhysicsScene() {}
};

#define IPHYSICSSCENE_H
#endif
