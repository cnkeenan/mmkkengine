#if !defined(IPHYSICS_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
class IPhysics : public ISystem
{
private:
protected:
public:

    ESystemType GetType() final { return ESystemType::PHYSICS; }
    virtual ~IPhysics() {}
};

#define IPHYSICS_H
#endif