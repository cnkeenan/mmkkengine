#if !defined(IAIOBJECT_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class IAIObject : public IObject
{
private:
protected:
public:

    ESystemType GetType() final { return ESystemType::AI; }
    virtual void BeginPlay() = 0;
    virtual void Tick(float DeltaTime) = 0;
    virtual bool IsInitialized() = 0;
    virtual ~IAIObject() {}
};

#define IAIOBJECT_H
#endif
