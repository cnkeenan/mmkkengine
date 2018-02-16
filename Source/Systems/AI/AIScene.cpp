/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

AIScene::AIScene()
{
    m_ObjectPool = gMemoryManager->GetPool(GetType());
    m_ObjectPool->CreatePool(sizeof(AIObject), NUMBER_OF_OBJECTS);
}

IAIObject* AIScene::CreateObject()
{
    //TODO(JJ): Object pool
    AIObject* Object = new AIObject();
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
        delete RealObject;        
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
    m_ObjectPool->DestroyPool();
}
