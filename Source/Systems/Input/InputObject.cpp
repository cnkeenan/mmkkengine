/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */    

void InputObject::Create()        
{
    m_IsInitialized = true;
}

void InputObject::Destroy() 
{
    m_IsInitialized = false;
}

bool InputObject::IsInitialized()
{
    return m_IsInitialized;
}

void* InputObject::operator new(size_t Size, void* Pointer)
{
    TObjectPool<InputObject>* ObjectPool = (TObjectPool<InputObject>*)Pointer;
    return ObjectPool->Create();        
}

void InputObject::operator delete(void* Object, void* Pointer)
{
    TObjectPool<InputObject>* ObjectPool = (TObjectPool<InputObject>*)Pointer;
    ObjectPool->Free((InputObject*)Object);
}

void InputObject::BeginPlay()
{
}

void InputObject::Tick(float DeltaTime)
{
}

