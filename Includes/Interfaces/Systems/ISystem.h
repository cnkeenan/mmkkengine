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

class IScene;

class ISystem
{
private:
protected:
public:

    virtual ESystemType GetType() = 0;
    inline void DestroyScene(IScene** Scene)
    {
        if((*Scene))
            delete (*Scene);

        (*Scene) = nullptr;
    };
    virtual ~ISystem() {}
};

#define ISYSTEM_H
#endif
