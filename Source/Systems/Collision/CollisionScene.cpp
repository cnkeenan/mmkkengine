/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

CollisionScene::CollisionScene()
{
    m_ObjectPool = gMemoryManager->GetPool(GetType());
    m_ObjectPool->CreatePool(sizeof(CollisionObject), NUMBER_OF_OBJECTS);
}

ICollisionObject* CollisionScene::CreateObject()
{
    CollisionObject* Object = new CollisionObject();
    Object->Create();    
    return Object;
}

void CollisionScene::DestroyObject(ICollisionObject* Object)
{
    if(Object->IsInitialized())
    {
        CollisionObject* RealObject = (CollisionObject*)Object;
        RealObject->Destroy();
        delete RealObject;
    }
}
    
void CollisionScene::BeginPlay()
{
}

void CollisionScene::Tick(float DeltaTime)
{
}

ITask* CollisionScene::GetTask()
{
    ITask* Result = (ITask*)&m_Task;
    return Result;
}
    
CollisionScene::~CollisionScene()
{
    //TODO(JJ): Destroy all valid objects first
    m_ObjectPool->DestroyPool();
}
