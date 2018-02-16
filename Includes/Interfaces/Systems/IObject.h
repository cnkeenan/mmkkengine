#if !defined(IOBJECT_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class IObject : public UObject
{
private:
protected:
public:

    IObject() {}
    virtual void BeginPlay() = 0;
    virtual void Tick(float DeltaTime) = 0;
    virtual ESystemType GetType() = 0;
    virtual bool IsInitialized() = 0;
    virtual ~IObject() {}
};

#define IOBJECT_H
#endif
