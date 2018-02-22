/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

WidgetScene::WidgetScene()
{
    m_ObjectPool.Initialize(NUMBER_OF_OBJECTS);
}

IWidgetObject* WidgetScene::CreateObject()
{
    WidgetObject* Object = new(&m_ObjectPool) WidgetObject();
    Object->Create();    
    return Object;
}

void WidgetScene::DestroyObject(IWidgetObject* Object)
{
    if(Object->IsInitialized())
    {
        WidgetObject* RealObject = (WidgetObject*)Object;
        RealObject->Destroy();
        WidgetObject::operator delete(&RealObject, &m_ObjectPool);
    }
}
    
void WidgetScene::BeginPlay()
{
}

void WidgetScene::Tick(float DeltaTime)
{
}

ITask* WidgetScene::GetTask()
{
    ITask* Result = (ITask*)&m_Task;
    return Result;
}
    
WidgetScene::~WidgetScene()
{
    //TODO(JJ): Destroy all valid objects first
    for(auto& Object : m_ObjectPool)
        Object.Destroy();
    m_ObjectPool.Destroy();
}
