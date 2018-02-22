/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

InputScene::InputScene()
{
    m_ObjectPool.Initialize(NUMBER_OF_OBJECTS);
}

IInputObject* InputScene::CreateObject()
{
    InputObject* Object = new(&m_ObjectPool) InputObject();
    Object->Create();    
    return Object;
}

void InputScene::DestroyObject(IInputObject* Object)
{
    if(Object->IsInitialized())
    {
        InputObject* RealObject = (InputObject*)Object;
        RealObject->Destroy();
        InputObject::operator delete(RealObject, &m_ObjectPool);
    }
}
    
void InputScene::BeginPlay()
{
}

void InputScene::Tick(float DeltaTime)
{
}

ITask* InputScene::GetTask()
{
    ITask* Result = (ITask*)&m_Task;
    return Result;
}
    
InputScene::~InputScene()
{
    //TODO(JJ): Destroy all valid objects first
    for(auto& Object : m_ObjectPool)
    {
        Object.Destroy();
    }
    m_ObjectPool.Destroy();    
}
