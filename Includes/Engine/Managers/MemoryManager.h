#if !defined(MEMORYMANAGER_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <Interfaces/Managers/IMemoryManager.h>

class MemoryManager : public IMemoryManager
{
private:

    ptr_size m_TotalAllocated;
    ptr_size m_CurrentUsed;
    ptr_size m_TotalFreed;

    MemoryManager();
    
public:

    static MemoryManager* Get()
    {
        //NOTE(EVERYONE): Since the memory manager will eventually track allocations, we shouldn't
        //allocate the manager on the heap. Warning in advance, we can't control when this manager
        //cleans up
        static MemoryManager s_MemoryManager;
        return &s_MemoryManager;
    }

    void* Allocate(ptr_size Size) final;
    void Free(void* Pointer) final;
};

#define MEMORYMANAGER_H
#endif
