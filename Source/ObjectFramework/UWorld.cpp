/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

void UWorld::Initialize(IAIScene* AIScene, ICollisionScene* CollisionScene,
                        IGraphicsScene* GraphicsScene, IInputScene* InputScene,
                        IPhysicsScene* PhysicsScene, ISoundScene* SoundScene,
                        ITransformScene* TransformScene, IWidgetScene* WidgetScene)
{
    m_AIScene = AIScene;
    m_CollisionScene = CollisionScene;
    m_GraphicsScene = GraphicsScene;
    m_InputScene = InputScene;
    m_PhysicsScene = PhysicsScene;
    m_SoundScene = SoundScene;
    m_TransformScene = TransformScene;
    m_WidgetScene = WidgetScene;
}

void UWorld::BeginPlay()
{
    UScene::BeginPlay();
    for(auto& Object : m_Objects)
        Object->BeginPlay();
    m_AIScene->BeginPlay();
    m_SoundScene->BeginPlay();
    m_WidgetScene->BeginPlay();
    m_InputScene->BeginPlay();
    m_CollisionScene->BeginPlay();
    m_PhysicsScene->BeginPlay();
    m_TransformScene->BeginPlay();
    m_GraphicsScene->BeginPlay();    
}

void UWorld::Tick(float DeltaTime)
{    
    UScene::Tick(DeltaTime);
    for(auto& Object : m_Objects)
        Object->Tick(DeltaTime);
    m_AIScene->Tick(DeltaTime);
    m_SoundScene->Tick(DeltaTime);
    m_WidgetScene->Tick(DeltaTime);
    m_InputScene->Tick(DeltaTime);
    m_CollisionScene->Tick(DeltaTime);
    m_PhysicsScene->Tick(DeltaTime);
    m_TransformScene->Tick(DeltaTime);
    m_GraphicsScene->Tick(DeltaTime);
}

void UWorld::AddObject(UObject* Object)
{
    m_Objects.push_back(Object);
}

FObjectConstructor* UWorld::GetObjectConstructor()
{
    return &m_ObjectConstructor;
}

void UWorld::RemoveObject(UObject** Object)
{
    for(int32 ObjectIndex = 0; ObjectIndex < m_Objects.size(); ObjectIndex++)
    {
        if(m_Objects[ObjectIndex] == (*Object))
        {
            m_Objects.erase(m_Objects.begin()+ObjectIndex);            
            delete (*Object);
            (*Object) = nullptr;
            break;
        }
    }

}

void UWorld::Destroy(IAI* AI, ICollision* Collision, IGraphics* Graphics, IInput* Input,
                     IPhysics* Physics, ISound* Sound, ITransform* Transform, IWidget* Widget)
{
    for(auto& Object : m_Objects)
    {        
        delete Object;
        Object = nullptr;
    }
    Widget->DestroyScene(&m_WidgetScene);
    Transform->DestroyScene(&m_TransformScene);
    Sound->DestroyScene(&m_SoundScene);
    Physics->DestroyScene(&m_PhysicsScene);
    Input->DestroyScene(&m_InputScene);
    Graphics->DestroyScene(&m_GraphicsScene);
    Collision->DestroyScene(&m_CollisionScene);
    AI->DestroyScene(&m_AIScene);    
}
