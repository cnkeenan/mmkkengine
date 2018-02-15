#if !defined(IGRAPHICSSCENE_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class IGraphicsScene : public IScene
{
private:
protected:
public:

    ESystemType GetType() final { return ESystemType::GRAPHICS; }
    virtual void BeginPlay() = 0;
    virtual void Tick() = 0;
    virtual ~IGraphicsScene() {}
};

#define IGRAPHICSSCENE_H
#endif
