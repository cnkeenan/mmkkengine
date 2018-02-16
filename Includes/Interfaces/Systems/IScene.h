#if !defined(ISCENE_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class IScene : public UScene
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
    std::vector<UObject*> m_Objects;
    
protected:
public:

    virtual void BeginPlay() = 0;
    virtual void Tick(float DeltaTime) = 0;
    virtual ESystemType GetType() = 0;
    virtual class ITask* GetTask() = 0;
    
    virtual ~IScene()
    {
        int x = 5;
    }
};

#define ISCENE_H
#endif
