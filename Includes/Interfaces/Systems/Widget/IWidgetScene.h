#if !defined(IWIDGETSCENE_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class IWidgetScene : public IScene
{
private:
protected:
public:

    virtual ESystemType GetType() final { return ESystemType::WIDGET; }
    virtual void BeginPlay() = 0;
    virtual void Tick() = 0;    
    
    virtual ~IWidgetScene() {}
};

#define IWIDGETSCENE_H
#endif
