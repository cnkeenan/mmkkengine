#if !defined(OBJECTCONSTRUCTOR_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class FObjectConstructor
{    
private:
    class IAIScene* m_AIScene;
    class ICollisionScene* m_CollisionScene;
    class IGraphicsScene* m_GraphicsScene;
    class IInputScene* m_InputScene;
    class IPhysicsScene* m_PhysicsScene;
    class ISoundScene* m_SoundScene;
    class ITransformScene* m_TransformScene;
    class IWidgetScene* m_WidgetScene;
    
public:

    template <typename T>
    T* Construct();

    
    void Destruct(class IObject* Object);
};

#define OBJECTCONSTRUCTOR_H
#endif
