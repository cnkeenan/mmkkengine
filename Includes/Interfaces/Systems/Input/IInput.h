#if !defined(IINPUT_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
class IInput : public ISystem
{
private:
protected:
public:

    ESystemType GetType() final { return ESystemType::INPUT; }
    virtual ~IInput() {}
};

#define IINPUT_H
#endif
