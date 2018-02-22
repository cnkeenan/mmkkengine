/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

TransformScene::TransformScene()
{
    m_ObjectPool.Initialize(NUMBER_OF_OBJECTS); 
}

ITransformObject* TransformScene::CreateObject()
{
    TransformObject* Object = new(&m_ObjectPool) TransformObject();
    Object->Create();    
    return Object;
}

void TransformScene::DestroyObject(ITransformObject* Object)
{
    if(Object->IsInitialized())
    {
        TransformObject* RealObject = (TransformObject*)Object;
        RealObject->Destroy();
        TransformObject::operator delete(RealObject, &m_ObjectPool);
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
    for(auto& Object : m_ObjectPool)
        Object.Destroy();
    m_ObjectPool.Destroy();
}
