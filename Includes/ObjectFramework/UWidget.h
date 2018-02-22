#if !defined(UWIDGET_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
class OBJECTFRAMEWORK_API UWidget : public UObject
{
private:
    class IWidgetObject* m_WidgetObject;
    class IGraphicsObject* m_GraphicsObject;
    
protected:

public:

    UWidget(FObjectConstructor* ObjectConstructor);

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual ~UWidget();
};

#define UWIDGET_H
#endif
