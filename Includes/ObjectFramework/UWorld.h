#if !defined(UWORLD_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class UObject;

class OBJECTFRAMEWORK_API UWorld : public UScene
{
    friend class FScheduler;    
private:    
    union
    {
        FObjectConstructor m_ObjectConstructor;
        struct
        {
            IAIScene* m_AIScene;
            ICollisionScene* m_CollisionScene;
            IGraphicsScene* m_GraphicsScene;
            IInputScene* m_InputScene;
            IPhysicsScene* m_PhysicsScene;
            ISoundScene* m_SoundScene;
            ITransformScene* m_TransformScene;
            IWidgetScene* m_WidgetScene;
        };
    };

    std::vector<UObject*> m_Objects;
    
public:

    void Initialize(IAIScene* AIScene, ICollisionScene* CollisionScene,
                    IGraphicsScene* GraphicsScene, IInputScene* InputScene,
                    IPhysicsScene* PhysicsScene, ISoundScene* SoundScene,
                    ITransformScene* TransformScene, IWidgetScene* WidgetScene);
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    void Destroy(class IAI* AI, class ICollision* Collision, class IGraphics* Graphics,
                 class IInput* Input, class IPhysics* Physics, class ISound* Sound,
                 class ITransform* Transform, class IWidget* Widget);
    void AddObject(UObject* Object);
    void RemoveObject(UObject** Object);
    FObjectConstructor* GetObjectConstructor();
    
    ~UWorld() {}
};

#define UWORLD_H
#endif
