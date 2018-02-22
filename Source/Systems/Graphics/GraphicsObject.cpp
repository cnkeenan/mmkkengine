/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */    

void GraphicsObject::Create() 
{
    m_IsInitialized = true;
}

void GraphicsObject::Destroy()
{
    m_IsInitialized = false;
}

bool GraphicsObject::IsInitialized()
{
    return m_IsInitialized;
}

void* GraphicsObject::operator new(size_t Size, void* Pointer)
{
    TObjectPool<GraphicsObject>* ObjectPool = (TObjectPool<GraphicsObject>*)Pointer;
    return ObjectPool->Create();    
}

void GraphicsObject::operator delete(void* Object, void* Pointer)
{
    TObjectPool<GraphicsObject>* ObjectPool = (TObjectPool<GraphicsObject>*)Pointer;
    ObjectPool->Free((GraphicsObject*)Object);        
}

void GraphicsObject::BeginPlay()
{
}

void GraphicsObject::Tick(float DeltaTime)
{
}

