#if !defined(IWIDGET_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
class IWidget : public ISystem
{
private:
protected:
public:

    virtual IWidgetScene* CreateScene() = 0;
    virtual void DestroyScene(IWidgetScene** Scene) = 0;
    ESystemType GetType() final { return ESystemType::WIDGET; }
    virtual ~IWidget() {}
};


//NOTE(EVERYONE): If we need managers add them here
typedef IWidget* fp_CreateWidgetSystem(class FLogger* Logger, class IMemoryManager* MemoryManager);
typedef void fp_DestroyWidgetSystem(IWidget** System);

#define IWIDGET_H
#endif
