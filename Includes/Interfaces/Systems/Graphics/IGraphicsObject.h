#if !defined(IGRAPHICSOBJECT_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class IGraphicsObject : public IObject
{
private:
protected:
public:

    ESystemType GetType() final { return ESystemType::GRAPHICS; }
    virtual void BeginPlay() = 0;
    virtual void Tick(float DeltaTime) = 0;
    virtual bool IsInitialized() = 0;
    virtual ~IGraphicsObject() {}
};

#define IGRAPHICSOBJECT_H
#endif
