#if !defined(IPHYSICSSCENE_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class IPhysicsScene : public IScene
{
private:
protected:
public:

    
    ESystemType GetType() final { return ESystemType::PHYSICS; }
    virtual void BeginPlay() = 0;
    virtual void Tick() = 0;

    virtual ~IPhysicsScene() {}
};

#define IPHYSICSSCENE_H
#endif
