#if !defined(IMEMORYMANAGER_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
class IMemoryManager
{
private:    
protected:
public:

    virtual void* Allocate(ptr_size Size) = 0;
    virtual void Free(void* Pointer) = 0;
};


void* operator new(ptr_size Size);
void* operator new[](ptr_size Size);
void operator delete(void* Pointer);
void operator delete[](void* Pointer);


#define IMEMORYMANAGER_H
#endif
