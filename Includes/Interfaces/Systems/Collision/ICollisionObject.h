#if !defined(ICOLLISIONOBJECT_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class ICollisionObject : public IObject
{
private:
protected:
public:

    ESystemType GetType() final { return ESystemType::COLLISION; }
    virtual void BeginPlay() = 0;
    virtual void Tick(float DeltaTime) = 0;
    virtual bool IsInitialized() = 0;
    virtual ~ICollisionObject() {}
};

#define ICOLLISIONOBJECT_H
#endif
