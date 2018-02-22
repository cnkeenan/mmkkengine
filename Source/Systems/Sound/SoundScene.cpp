/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

SoundScene::SoundScene()
{    
    m_ObjectPool.Initialize(NUMBER_OF_OBJECTS);
}

ISoundObject* SoundScene::CreateObject()
{
    SoundObject* Object = new(&m_ObjectPool) SoundObject();
    Object->Create();    
    return Object;
}

void SoundScene::DestroyObject(ISoundObject* Object)
{
    if(Object->IsInitialized())
    {
        SoundObject* RealObject = (SoundObject*)Object;
        RealObject->Destroy();
        SoundObject::operator delete(RealObject, &m_ObjectPool);
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
    for(auto& Object : m_ObjectPool)
        Object.Destroy();
    m_ObjectPool.Destroy();
}
