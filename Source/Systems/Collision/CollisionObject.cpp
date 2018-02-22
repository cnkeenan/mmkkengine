/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */    

void CollisionObject::Create() 
{
    m_IsInitialized = true;
}

void CollisionObject::Destroy() 
{
    m_IsInitialized = false;
}

bool CollisionObject::IsInitialized()
{
    return m_IsInitialized;
}

void* CollisionObject::operator new(size_t Size, void* Pointer)
{
    TObjectPool<CollisionObject>* ObjectPool = (TObjectPool<CollisionObject>*)Pointer;
    return ObjectPool->Create();    
}

void CollisionObject::operator delete(void* Object, void* Pointer)
{
    TObjectPool<CollisionObject>* ObjectPool = (TObjectPool<CollisionObject>*)Pointer;
    ObjectPool->Free((CollisionObject*)Object);        
}

void CollisionObject::BeginPlay()
{    
}

void CollisionObject::Tick(float DeltaTime)
{
}

