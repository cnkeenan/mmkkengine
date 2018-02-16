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

void* PhysicsObject::operator new(size_t Size)
{
    return gMemoryManager->GetPool(ESystemType::PHYSICS)->Allocate();
}

void PhysicsObject::operator delete(void* Object)
{
    gMemoryManager->GetPool(ESystemType::PHYSICS)->Free(Object);
}

void PhysicsObject::BeginPlay()
{
}

void PhysicsObject::Tick(float DeltaTime)
{
}

