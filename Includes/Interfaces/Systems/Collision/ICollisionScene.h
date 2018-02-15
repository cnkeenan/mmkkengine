#if !defined(ICOLLISIONSCENE_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class ICollisionScene : public IScene
{
private:
protected:
public:
        
    virtual ICollisionObject* CreateObject() = 0;
    virtual void DestroyObject(ICollisionObject** Object) = 0;        
    
    ESystemType GetType() final { return ESystemType::COLLISION; }
    virtual void BeginPlay() = 0;
    virtual void Tick(float DeltaTime) = 0;
    virtual ITask* GetTask() = 0;
    
    virtual ~ICollisionScene() {}
};

#define ICOLLISIONSCENE_H
#endif
