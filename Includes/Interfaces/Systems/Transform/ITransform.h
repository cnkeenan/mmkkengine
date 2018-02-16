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
    virtual void DestroyScene(ITransformScene** Scene) = 0;
    ESystemType GetType() final { return ESystemType::TRANSFORM; }
    virtual ~ITransform() {}
};


//NOTE(EVERYONE): If we need managers add them here
typedef ITransform* fp_CreateTransformSystem(class IMemoryManager* MemoryManager);
typedef void fp_DestroyTransformSystem(ITransform** System);


#define ITRANSFORM_H
#endif
