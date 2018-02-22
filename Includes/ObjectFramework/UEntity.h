#if !defined(UENTITY_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class OBJECTFRAMEWORK_API UEntity : public UObject
{
private:
    class ITransformObject* m_TransformObject;
    class ICollisionObject* m_CollisionObject;
    class IPhysicsObject* m_PhysicsObject;
    class ISoundObject* m_SoundObject;
protected:


public:

    UEntity(FObjectConstructor* ObjectConstructor);

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    
    virtual ~UEntity();
};

#define UENTITY_H
#endif
