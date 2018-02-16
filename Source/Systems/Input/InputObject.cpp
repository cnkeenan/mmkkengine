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

void* InputObject::operator new(size_t Size)
{
    return gMemoryManager->GetPool(ESystemType::INPUT)->Allocate();
}

void InputObject::operator delete(void* Object)
{
    return gMemoryManager->GetPool(ESystemType::INPUT)->Free(Object);
}

void InputObject::BeginPlay()
{
}

void InputObject::Tick(float DeltaTime)
{
}

