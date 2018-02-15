#if !defined(ITRANSFORMSCENE_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class ITransformScene : public IScene
{
private:
protected:
public:

    ESystemType GetType() final { return ESystemType::TRANSFORM; }
    virtual void BeginPlay() = 0;
    virtual void Tick() = 0;

    virtual ~ITransformScene() {}
};

#define ITRANSFORMSCENE_H
#endif
