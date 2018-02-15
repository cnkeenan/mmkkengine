#if !defined(IWIDGET_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
class IWidget : public ISystem
{
private:
protected:
public:

    ESystemType GetType() final { return ESystemType::WIDGET; }
    virtual ~IWidget() {}
};

#define IWIDGET_H
#endif
