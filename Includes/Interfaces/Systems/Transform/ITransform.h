#if !defined(ITRANSFORM_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
class ITransform : public ISystem
{
private:
protected:
public:

    virtual ITransformScene* CreateScene() = 0;
    ESystemType GetType() final { return ESystemType::TRANSFORM; }
    virtual ~ITransform() {}
};

#define ITRANSFORM_H
#endif
