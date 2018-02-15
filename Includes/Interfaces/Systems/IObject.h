#if !defined(IOBJECT_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class IObject : public UObject
{
private:
protected:
public:

    virtual void BeginPlay() = 0;
    virtual void Tick(float DeltaTime) = 0;
    virtual ESystemType GetType() = 0;
    virtual ~IObject() {}
};

#define IOBJECT_H
#endif
