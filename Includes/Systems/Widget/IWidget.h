#if !defined(IWIDGET_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
class IWidget : public ISystem
{
private:
protected:
public:
                                
    virtual IWidgetObject* CreateObject() = 0;
    virtual void DestroyObject(IWidgetObject** Object) = 0;                

    virtual IWidgetScene* CreateScene() = 0;
    ESystemType GetType() final { return ESystemType::WIDGET; }
    virtual ~IWidget() {}
};

#define IWIDGET_H
#endif
