/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

CollisionScene::CollisionScene()
{
    m_ObjectPool.Initialize(NUMBER_OF_OBJECTS);    
}

ICollisionObject* CollisionScene::CreateObject()
{
    CollisionObject* Object = new(&m_ObjectPool) CollisionObject();
    Object->Create();    
    return Object;
}

void CollisionScene::DestroyObject(ICollisionObject* Object)
{
    if(Object->IsInitialized())
    {
        CollisionObject* RealObject = (CollisionObject*)Object;
        RealObject->Destroy();
        CollisionObject::operator delete(RealObject, &m_ObjectPool);
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
    for(auto& Object : m_ObjectPool)
    {
        Object.Destroy();
    }     
    m_ObjectPool.Destroy();
}
