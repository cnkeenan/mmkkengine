#if !defined(IINPUTOBJECT_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class IInputObject : public IObject
{
private:
protected:
public:

    ESystemType GetType() final { return ESystemType::INPUT; }
    virtual void BeginPlay() = 0;
    virtual void Tick(float DeltaTime) = 0;
    virtual ~IInputObject() {}
};

#define IINPUTOBJECT_H
#endif
