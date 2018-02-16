#if !defined(IWIDGETSCENE_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class IWidgetScene : public IScene
{
private:
protected:
public:

    
    virtual IWidgetObject* CreateObject() = 0;
    virtual void DestroyObject(IWidgetObject* Object) = 0;    
    
    virtual ESystemType GetType() final { return ESystemType::WIDGET; }
    virtual void BeginPlay() = 0;
    virtual void Tick(float DeltaTime) = 0;    
    virtual ITask* GetTask() = 0;
    
    virtual ~IWidgetScene() {}
};

#define IWIDGETSCENE_H
#endif
