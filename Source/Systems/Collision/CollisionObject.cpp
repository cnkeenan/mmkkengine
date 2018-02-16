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

void* CollisionObject::operator new(size_t Size)
{
    return gMemoryManager->GetPool(ESystemType::COLLISION)->Allocate();
}

void CollisionObject::operator delete(void* Object)
{
    gMemoryManager->GetPool(ESystemType::COLLISION)->Free(Object);
}

void CollisionObject::BeginPlay()
{    
}

void CollisionObject::Tick(float DeltaTime)
{
}

