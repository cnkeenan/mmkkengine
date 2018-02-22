/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */    

void WidgetObject::Create() 
{
    m_IsInitialized = true;
}

void WidgetObject::Destroy() 
{
    m_IsInitialized = false;
}

bool WidgetObject::IsInitialized()
{
    return m_IsInitialized;
}

void* WidgetObject::operator new(size_t Size, void* Pointer)
{
    TObjectPool<WidgetObject>* ObjectPool = (TObjectPool<WidgetObject>*)Pointer;
    return ObjectPool->Create();    
}

void WidgetObject::operator delete(void* Object, void* Pointer)
{
    TObjectPool<WidgetObject>* ObjectPool = (TObjectPool<WidgetObject>*)Pointer;
    ObjectPool->Free((WidgetObject*)Object);        
}

void WidgetObject::BeginPlay()
{
}

void WidgetObject::Tick(float DeltaTime)
{
}

