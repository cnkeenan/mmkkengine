#if !defined(IAISCENE_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class IAIScene : public IScene
{
private:
protected:
public:

    ESystemType GetType() final { return ESystemType::AI; }
    virtual void BeginPlay() = 0;
    virtual void Tick() = 0;

    virtual ~IAIScene() {}
};

#define IAISCENE_H
#endif
