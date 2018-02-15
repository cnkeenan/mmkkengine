#if !defined(ICOLLISIONSCENE_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class ICollisionScene : public IScene
{
private:
protected:
public:

    ESystemType GetType() final { return ESystemType::COLLISION; }
    virtual void BeginPlay() = 0;
    virtual void Tick() = 0;
    
    virtual ~ICollisionScene() {}
};

#define ICOLLISIONSCENE_H
#endif
