/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

SoundScene::SoundScene()
{
    m_ObjectPool = gMemoryManager->GetPool(GetType());
    m_ObjectPool->CreatePool(sizeof(SoundObject), NUMBER_OF_OBJECTS);
}

ISoundObject* SoundScene::CreateObject()
{
    SoundObject* Object = new SoundObject();
    Object->Create();    
    return Object;
}

void SoundScene::DestroyObject(ISoundObject* Object)
{
    if(Object->IsInitialized())
    {
        SoundObject* RealObject = (SoundObject*)Object;
        RealObject->Destroy();
        delete RealObject;
    }
}
    
void SoundScene::BeginPlay()
{
}

void SoundScene::Tick(float DeltaTime)
{
}

ITask* SoundScene::GetTask()
{
    ITask* Result = (ITask*)&m_Task;
    return Result;
}
    
SoundScene::~SoundScene()
{
    //TODO(JJ): Destroy all valid objects first
    m_ObjectPool->DestroyPool();
}
