/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */    

void SoundObject::Create() 
{
    m_IsInitialized = true;
}

void SoundObject::Destroy() 
{
    m_IsInitialized = false;
}

bool SoundObject::IsInitialized()
{
    return m_IsInitialized;
}

void* SoundObject::operator new(size_t Size, void* Pointer)
{
    TObjectPool<SoundObject>* ObjectPool = (TObjectPool<SoundObject>*)Pointer;
    return ObjectPool->Create();    
}

void SoundObject::operator delete(void* Object, void* Pointer)
{
    TObjectPool<SoundObject>* ObjectPool = (TObjectPool<SoundObject>*)Pointer;
    ObjectPool->Free((SoundObject*)Object);        
}

void SoundObject::BeginPlay()
{
}

void SoundObject::Tick(float DeltaTime)
{
}

