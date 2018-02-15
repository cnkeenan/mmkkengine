#if !defined(ICOLLISION_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
class ICollision : public ISystem
{
private:
protected:
public:

    ESystemType GetType() final { return ESystemType::COLLISION; }
    virtual ~ICollision() {}
};

#define ICOLLISION_H
#endif
