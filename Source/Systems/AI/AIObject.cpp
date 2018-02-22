/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

void AIObject::Create() 
{
    m_IsInitialized = true;
}

void AIObject::Destroy() 
{
    m_IsInitialized = false;
}

bool AIObject::IsInitialized()
{
    return m_IsInitialized;
}

void* AIObject::operator new(size_t Size, void* Pointer)
{
    TObjectPool<AIObject>* ObjectPool = (TObjectPool<AIObject>*)Pointer;
    return ObjectPool->Create();
}

void AIObject::operator delete(void* Object, void* Pointer)
{
    TObjectPool<AIObject>* ObjectPool = (TObjectPool<AIObject>*)Pointer;
    return ObjectPool->Free((AIObject*)Object);
}

void AIObject::BeginPlay()
{
}

void AIObject::Tick(float DeltaTime)
{
}
