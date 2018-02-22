/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

MemoryManager::MemoryManager() : m_TotalAllocated(0), m_CurrentUsed(0), m_TotalFreed(0)
{
}

void* MemoryManager::Allocate(ptr_size Size)
{
    m_TotalAllocated += Size;
    m_CurrentUsed += Size;

    ptr_size ActualSize = Size + sizeof(ptr_size);
    uint8* Result = (uint8*)malloc(ActualSize);
    *(size_t*)Result = Size;
    Result += sizeof(ptr_size);
    return Result;
}

void MemoryManager::Free(void* Pointer)
{
    void* Memory = (void*)((size_t*)Pointer-1);
    ptr_size Size = *(ptr_size*)Memory;
    m_TotalFreed += Size;
    m_CurrentUsed -= Size;

    free(Memory);
}

void* operator new(ptr_size Size)
{
    return MemoryManager::Get()->Allocate(Size);
}

void* operator new[](ptr_size Size)
{
    return MemoryManager::Get()->Allocate(Size);
}

void operator delete(void* Pointer)
{
    MemoryManager::Get()->Free(Pointer);
}

void operator delete[](void* Pointer)
{
    MemoryManager::Get()->Free(Pointer);
}
