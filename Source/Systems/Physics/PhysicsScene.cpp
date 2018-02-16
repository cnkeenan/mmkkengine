/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

PhysicsScene::PhysicsScene()
{
    m_ObjectPool = gMemoryManager->GetPool(GetType());
    m_ObjectPool->CreatePool(sizeof(PhysicsObject), NUMBER_OF_OBJECTS);
}

IPhysicsObject* PhysicsScene::CreateObject()
{
    PhysicsObject* Object = new PhysicsObject();
    Object->Create();
    return Object;
}

void PhysicsScene::DestroyObject(IPhysicsObject* Object)
{
    if(Object->IsInitialized())
    {
        PhysicsObject* RealObject = (PhysicsObject*)Object;
        RealObject->Destroy();
        delete RealObject;
    }
}
    
void PhysicsScene::BeginPlay()
{
}

void PhysicsScene::Tick(float DeltaTime)
{
}

ITask* PhysicsScene::GetTask()
{
    ITask* Result = (ITask*)&m_Task;
    return Result;
}
    
PhysicsScene::~PhysicsScene()
{
    //TODO(JJ): Destroy all valid objects first
    m_ObjectPool->DestroyPool();    
}
