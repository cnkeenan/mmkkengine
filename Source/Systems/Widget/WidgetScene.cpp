/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

WidgetScene::WidgetScene()
{
    m_ObjectPool = gMemoryManager->GetPool(GetType());
    m_ObjectPool->CreatePool(sizeof(WidgetObject), NUMBER_OF_OBJECTS);
}

IWidgetObject* WidgetScene::CreateObject()
{
    WidgetObject* Object = new WidgetObject();
    Object->Create();    
    return Object;
}

void WidgetScene::DestroyObject(IWidgetObject* Object)
{
    if(Object->IsInitialized())
    {
        WidgetObject* RealObject = (WidgetObject*)Object;
        RealObject->Destroy();
        delete RealObject;
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
    m_ObjectPool->DestroyPool();
}
