/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

GraphicsScene::GraphicsScene()
{    
    m_ObjectPool.Initialize(NUMBER_OF_OBJECTS);
}

IGraphicsObject* GraphicsScene::CreateObject()
{
    GraphicsObject* Object = new(&m_ObjectPool) GraphicsObject();
    Object->Create();    
    return Object;
}

void GraphicsScene::DestroyObject(IGraphicsObject* Object)
{
    if(Object->IsInitialized())
    {
        GraphicsObject* RealObject = (GraphicsObject*)Object;
        RealObject->Destroy();
        GraphicsObject::operator delete(RealObject, &m_ObjectPool);
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
    for(auto& Object : m_ObjectPool)
    {
        Object.Destroy();
    }
    m_ObjectPool.Destroy();
}
