/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

GraphicsScene::GraphicsScene()
{
    m_ObjectPool = gMemoryManager->GetPool(GetType());
    m_ObjectPool->CreatePool(sizeof(GraphicsObject), NUMBER_OF_OBJECTS);
}

IGraphicsObject* GraphicsScene::CreateObject()
{
    GraphicsObject* Object = new GraphicsObject();
    Object->Create();    
    return Object;
}

void GraphicsScene::DestroyObject(IGraphicsObject* Object)
{
    if(Object->IsInitialized())
    {
        GraphicsObject* RealObject = (GraphicsObject*)Object;
        RealObject->Destroy();
        delete RealObject;
    }
}
    
void GraphicsScene::BeginPlay()
{
}

void GraphicsScene::Tick(float DeltaTime)
{
}

ITask* GraphicsScene::GetTask()
{
    ITask* Result = (ITask*)&m_Task;
    return Result;
}
    
GraphicsScene::~GraphicsScene()
{
    //TODO(JJ): Destroy all valid objects first
    m_ObjectPool->DestroyPool();
}
