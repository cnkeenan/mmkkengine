/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */    

void SoundObject::Create() 
{
    m_IsInitialized = true;
}

void SoundObject::Destroy() 
{
    m_IsInitialized = false;
}

bool SoundObject::IsInitialized()
{
    return m_IsInitialized;
}

void* SoundObject::operator new(size_t Size)
{
    return gMemoryManager->GetPool(ESystemType::SOUND)->Allocate();
}

void SoundObject::operator delete(void* Object)
{
    gMemoryManager->GetPool(ESystemType::SOUND)->Free(Object);
}

void SoundObject::BeginPlay()
{
}

void SoundObject::Tick(float DeltaTime)
{
}

