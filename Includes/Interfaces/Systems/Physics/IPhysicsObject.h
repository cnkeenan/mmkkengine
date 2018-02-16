#if !defined(IPHYSICSOBJECT_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class IPhysicsObject : public IObject
{
private:
protected:
public:

    
    ESystemType GetType() final { return ESystemType::PHYSICS; }
    virtual void BeginPlay() = 0;
    virtual void Tick(float DeltaTime) = 0;
    virtual bool IsInitialized() = 0;
    virtual ~IPhysicsObject() {}
};

#define IPHYSICSOBJECT_H
#endif
