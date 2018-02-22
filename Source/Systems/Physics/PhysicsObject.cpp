/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */    

void PhysicsObject::Create() 
{
    m_IsInitialized = true;
}

void PhysicsObject::Destroy() 
{
    m_IsInitialized = false;
}

bool PhysicsObject::IsInitialized()
{
    return m_IsInitialized;
}

void* PhysicsObject::operator new(size_t Size, void* Pointer)
{
    TObjectPool<PhysicsObject>* ObjectPool = (TObjectPool<PhysicsObject>*)Pointer;
    return ObjectPool->Create();    
}

void PhysicsObject::operator delete(void* Object, void* Pointer)
{
    TObjectPool<PhysicsObject>* ObjectPool = (TObjectPool<PhysicsObject>*)Pointer;
    ObjectPool->Free((PhysicsObject*)Object);        
}

void PhysicsObject::BeginPlay()
{
}

void PhysicsObject::Tick(float DeltaTime)
{
}

