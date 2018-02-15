#if !defined(OBJECTCONSTRUCTOR_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class FObjectConstructor
{
private:
public:

    template <typename T>
    T* Construct();

    
    void Destruct(class IObject** Object);
};

#define OBJECTCONSTRUCTOR_H
#endif
