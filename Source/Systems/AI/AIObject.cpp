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

void* AIObject::operator new(size_t Size)
{    
    return gMemoryManager->GetPool(ESystemType::AI)->Allocate();
}

void AIObject::operator delete(void* Object)
{    
    return gMemoryManager->GetPool(ESystemType::AI)->Free(Object);
}

void AIObject::BeginPlay()
{
}

void AIObject::Tick(float DeltaTime)
{
}
