#if !defined(ITRANSFORMOBJECT_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class ITransformObject : public IObject
{
private:
protected:
public:

    ESystemType GetType() final { return ESystemType::TRANSFORM; }
    virtual void BeginPlay() = 0;
    virtual void Tick(float DeltaTime) = 0;
    virtual ~ITransformObject() {}
};

#define ITRANSFORMOBJECT_H
#endif
