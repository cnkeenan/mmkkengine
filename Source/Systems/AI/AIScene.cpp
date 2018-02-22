/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
AIScene::AIScene()
{
    m_ObjectPool.Initialize(NUMBER_OF_OBJECTS);
}

IAIObject* AIScene::CreateObject()
{
    //TODO(JJ): Object pool
    AIObject* Object = new(&m_ObjectPool) AIObject();
    Object->Create();
    return Object;
}

void AIScene::DestroyObject(IAIObject* Object)
{
    //TODO(JJ): Object pool
    if(Object->IsInitialized())
    {
        AIObject* RealObject = (AIObject*)Object;
        RealObject->Destroy();
        AIObject::operator delete(RealObject, &m_ObjectPool);        
    }
}


void AIScene::BeginPlay()
{
}

void AIScene::Tick(float DeltaTime)
{
}

ITask* AIScene::GetTask()
{
    ITask* Result = (ITask*)&m_Task;
    return Result;
}

AIScene::~AIScene()
{
    //TODO(JJ): Destroy all valid objects first
    for(auto& Object : m_ObjectPool)
    {
        Object.Destroy();
    }
    m_ObjectPool.Destroy();
}
