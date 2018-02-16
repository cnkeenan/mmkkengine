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

void* TransformObject::operator new(size_t Size)
{
    return gMemoryManager->GetPool(ESystemType::TRANSFORM)->Allocate();    
}

void TransformObject::operator delete(void* Object)
{
    gMemoryManager->GetPool(ESystemType::TRANSFORM)->Free(Object);
}

void TransformObject::Tick(float DeltaTime)
{
}

