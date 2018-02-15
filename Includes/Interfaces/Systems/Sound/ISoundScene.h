#if !defined(ISOUNDSCENE_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class ISoundScene : public IScene
{
private:
protected:
public:

    ESystemType GetType() final { return ESystemType::SOUND; }
    virtual void BeginPlay() = 0;
    virtual void Tick() = 0;

    virtual ~ISoundScene() {}
};

#define ISOUNDSCENE_H
#endif
