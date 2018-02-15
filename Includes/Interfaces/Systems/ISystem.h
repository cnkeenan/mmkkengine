#if !defined(ISYSTEM_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

enum class ESystemType
{
    AI,
    COLLISION,
    GRAPHICS,
    INPUT,
    PHYSICS,
    SOUND,
    TRANSFORM,
    WIDGET
};

class ISystem
{
private:
protected:
public:

    virtual ESystemType GetType() = 0;
    virtual ~ISystem() {}
};

#define ISYSTEM_H
#endif
