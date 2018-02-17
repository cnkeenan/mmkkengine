#if !defined(LOADER_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

//NOTE(EVERYONE): This class is responsible for loading the systems. Holds the
//pointers for each system interface
class FLoader
{
private:
    IAI* m_AI;
    ICollision* m_Collision;
    IGraphics* m_Graphics;
    IInput* m_Input;
    IPhysics* m_Physics;
    ISound* m_Sound;
    ITransform* m_Transform;
    IWidget* m_Widget;
    
public:
    FLoader();
    void Initialize(IWindow* Window);
    UWorld* Load();
    void Unload(UWorld* World);
    ~FLoader();
};

#define LOADER_H
#endif
