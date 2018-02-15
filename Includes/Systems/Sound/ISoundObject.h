#if !defined(ISOUNDOBJECT_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class ISoundObject : public IObject
{
private:
protected:
public:

    ESystemType GetType() final { return ESystemType::SOUND; }
    virtual void BeginPlay() = 0;
    virtual void Tick(float DeltaTime) = 0;
    virtual ~ISoundObject() {}
};

#define ISOUNDOBJECT_H
#endif
