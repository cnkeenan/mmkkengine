/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

PhysicsScene::PhysicsScene()
{    
    m_ObjectPool.Initialize(NUMBER_OF_OBJECTS);
}

IPhysicsObject* PhysicsScene::CreateObject()
{
    PhysicsObject* Object = new(&m_ObjectPool) PhysicsObject();
    Object->Create();
    return Object;
}

void PhysicsScene::DestroyObject(IPhysicsObject* Object)
{
    if(Object->IsInitialized())
    {
        PhysicsObject* RealObject = (PhysicsObject*)Object;
        RealObject->Destroy();
        PhysicsObject::operator delete(RealObject, &m_ObjectPool);
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
    for(auto& Object : m_ObjectPool)
        Object.Destroy();
    m_ObjectPool.Destroy();    
}
