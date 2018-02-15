#if !defined(IINPUTSCENE_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class IInputScene : public IScene
{
private:
protected:
public:

    ESystemType GetType() final { return ESystemType::INPUT; }
    virtual void BeginPlay() = 0;
    virtual void Tick() = 0;

    virtual ~IInputScene() {}
};

#define IINPUTSCENE_H
#endif