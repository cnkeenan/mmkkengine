/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

InputScene::InputScene()
{
    m_ObjectPool = gMemoryManager->GetPool(GetType());
    m_ObjectPool->CreatePool(sizeof(InputObject), NUMBER_OF_OBJECTS);
}

IInputObject* InputScene::CreateObject()
{
    InputObject* Object = new InputObject();
    Object->Create();    
    return Object;
}

void InputScene::DestroyObject(IInputObject* Object)
{
    if(Object->IsInitialized())
    {
        InputObject* RealObject = (InputObject*)Object;
        RealObject->Destroy();
        delete RealObject;
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
    m_ObjectPool->DestroyPool();    
}
