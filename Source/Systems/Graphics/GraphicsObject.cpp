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

void* GraphicsObject::operator new(size_t Size)
{
    return gMemoryManager->GetPool(ESystemType::GRAPHICS)->Allocate();
}

void GraphicsObject::operator delete(void* Object)
{
    gMemoryManager->GetPool(ESystemType::GRAPHICS)->Free(Object);
}

void GraphicsObject::BeginPlay()
{
}

void GraphicsObject::Tick(float DeltaTime)
{
}

