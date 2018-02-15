/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

AIScene::AIScene()
{
}

IAIObject* AIScene::CreateObject()
{
    //TODO(JJ): Object pool
    AIObject* Object = (AIObject*)operator new (sizeof(AIObject));
    Object->Create();
    m_Objects.push_back(Object);
    return Object;
}

void AIScene::DestroyObject(IAIObject** Object)
{
    //TODO(JJ): Object pool
    if((*Object))
    {
        AIObject** RealObject = (AIObject**)Object; 
        for(uint32 ObjectIndex = 0; ObjectIndex < m_Objects.size(); ObjectIndex++)
        {
            if((*RealObject) == m_Objects[ObjectIndex])
            {
                m_Objects.erase(m_Objects.begin()+ObjectIndex);
                (*RealObject)->Destroy();
                operator delete((*RealObject));
                (*RealObject) = nullptr;
            }
        }
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
}
