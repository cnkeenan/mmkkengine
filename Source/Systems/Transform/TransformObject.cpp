/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */    

void TransformObject::Create() 
{
    m_IsInitialized = true;
}

void TransformObject::Destroy() 
{
    m_IsInitialized = false;
}

bool TransformObject::IsInitialized()
{
    return m_IsInitialized;
}

void TransformObject::BeginPlay()
{
}

void* TransformObject::operator new(size_t Size, void* Pointer)
{
    TObjectPool<TransformObject>* ObjectPool = (TObjectPool<TransformObject>*)Pointer;
    return ObjectPool->Create();    
}

void TransformObject::operator delete(void* Object, void* Pointer)
{
    TObjectPool<TransformObject>* ObjectPool = (TObjectPool<TransformObject>*)Pointer;
    ObjectPool->Free((TransformObject*)Object);        
}

void TransformObject::Tick(float DeltaTime)
{
}

