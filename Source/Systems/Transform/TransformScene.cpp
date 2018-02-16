/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

TransformScene::TransformScene()
{
    m_ObjectPool = gMemoryManager->GetPool(GetType());
    m_ObjectPool->CreatePool(sizeof(TransformObject), NUMBER_OF_OBJECTS); 
}

ITransformObject* TransformScene::CreateObject()
{
    TransformObject* Object = new TransformObject();
    Object->Create();    
    return Object;
}

void TransformScene::DestroyObject(ITransformObject* Object)
{
    if(Object->IsInitialized())
    {
        TransformObject* RealObject = (TransformObject*)Object;
        RealObject->Destroy();
        delete RealObject;
    }
}
    
void TransformScene::BeginPlay()
{
}

void TransformScene::Tick(float DeltaTime)
{
}

ITask* TransformScene::GetTask()
{
    ITask* Result = (ITask*)&m_Task;
    return Result;
}
    
TransformScene::~TransformScene()
{
    //TODO(JJ): Destroy all valid objects first
    m_ObjectPool->DestroyPool();
}
