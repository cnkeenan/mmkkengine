#if !defined(IAI_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
class IAI : public ISystem
{
private:
protected:
public:

    ESystemType GetType() final { return ESystemType::AI; }
    virtual ~IAI() {}
};

#define IAI_H
#endif
