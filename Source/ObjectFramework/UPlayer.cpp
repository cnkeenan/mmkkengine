/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

UPlayer::UPlayer(ITransformObject* TransformObject, IInputObject* InputObject,
                 IRenderingObject* RenderingObject, ICollisionObject* CollisionObject,
                 IPhysicsObject* PhysicsObject, ISoundObject* SoundObject) :
        UActor(TransformObject, RenderingObject, CollisionObject, PhysicsObject, SoundObject),
        m_InputObject(InputObject)
{}

UPlayer::~UPlayer()
{
}
