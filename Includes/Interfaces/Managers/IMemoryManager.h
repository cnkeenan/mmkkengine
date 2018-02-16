#if !defined(IMEMORYMANAGER_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <Utility/Pool.h>

#define POOL_EXPOSE(x) \
    friend class x##Scene; \
    friend class x##Object   

class IMemoryManager
{
private:
    POOL_EXPOSE(AI);
    POOL_EXPOSE(Collision);
    POOL_EXPOSE(Graphics);
    POOL_EXPOSE(Input);
    POOL_EXPOSE(Physics);
    POOL_EXPOSE(Sound);
    POOL_EXPOSE(Transform);
    POOL_EXPOSE(Widget);

    virtual FPool* GetPool(ESystemType Type) = 0;
protected:
public:
};

#define IMEMORYMANAGER_H
#endif
