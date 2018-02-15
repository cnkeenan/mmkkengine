#if !defined(ITRANSFORM_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
class ITransform : public ISystem
{
private:
protected:
public:

    ESystemType GetType() final { return ESystemType::TRANSFORM; }
    virtual ~ITransform() {}
};

#define ITRANSFORM_H
#endif
