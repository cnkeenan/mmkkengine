#if !defined(MEMORYMANAGER_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <Interfaces/Managers/IMemoryManager.h>
#include <Utility/Pool.h>

class MemoryManager : public IMemoryManager
{
private:
    FPool m_AIPool;
    FPool m_CollisionPool;
    FPool m_GraphicsPool;
    FPool m_InputPool;
    FPool m_PhysicsPool;
    FPool m_SoundPool;
    FPool m_TransformPool;
    FPool m_WidgetPool;

    FPool* GetPool(ESystemType Type);
    
public:

    static MemoryManager* Get()
    {
        //NOTE(EVERYONE): Since the memory manager will eventually track allocations, we shouldn't
        //allocate the manager on the heap. Warning in advance, we can't control when this manager
        //cleans up
        static MemoryManager s_MemoryManager;
        return &s_MemoryManager;
    }
};

#define MEMORYMANAGER_H
#endif
