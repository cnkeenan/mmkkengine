#if !defined(IINPUT_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
class IInput : public ISystem
{
private:
protected:
public:

    virtual IInputScene* CreateScene() = 0;
    ESystemType GetType() final { return ESystemType::INPUT; }
    virtual ~IInput() {}
};

#define IINPUT_H
#endif
