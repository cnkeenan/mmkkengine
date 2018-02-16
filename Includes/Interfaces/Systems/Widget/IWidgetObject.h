#if !defined(IWIDGETOBJECT_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class IWidgetObject : public IObject
{
private:
protected:
public:

    virtual ESystemType GetType() final { return ESystemType::WIDGET; }
    virtual void BeginPlay() = 0;
    virtual void Tick(float DeltaTime) = 0;
    virtual bool IsInitialized() = 0;
    virtual ~IWidgetObject() {}
};

#define IWIDGETOBJECT_H
#endif
