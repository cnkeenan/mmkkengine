#if !defined(UPLAYER_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class OBJECTFRAMEWORK_API UPlayer : public UActor
{
private:
    class IInputObject* m_InputObject;
protected:
public:
    
    UPlayer(ITransformObject* TransformObject, IInputObject* InputObject,
            IRenderingObject* RenderingObject=nullptr, ICollisionObject* CollisionObject=nullptr,
            IPhysicsObject* PhysicsObject=nullptr, ISoundObject* SoundObject=nullptr);

    virtual ~UPlayer();
};

#define UPLAYER_H
#endif
