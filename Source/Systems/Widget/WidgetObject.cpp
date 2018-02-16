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

void* WidgetObject::operator new(size_t Size)
{
    return gMemoryManager->GetPool(ESystemType::WIDGET)->Allocate();
}

void WidgetObject::operator delete(void* Object)
{
    gMemoryManager->GetPool(ESystemType::WIDGET)->Free(Object);
}

void WidgetObject::BeginPlay()
{
}

void WidgetObject::Tick(float DeltaTime)
{
}

