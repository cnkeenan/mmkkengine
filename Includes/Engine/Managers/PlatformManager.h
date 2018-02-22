#if !defined(PLATFORMMANAGER_H)
template <typename T>
class FThread;

    
#if defined(CreateWindow)
#undef CreateWindow
#endif

#if defined(CreateMutex)
#undef CreateMutex
#endif

#if defined(CreateSemaphore)
#undef CreateSemaphore
#endif

class PlatformManager : public IPlatformManager
{
private:
    static PlatformManager* s_PlatformManager;
    FOpenGL m_OpenGL;

    PlatformManager()
    {
        m_OpenGL = {};
    }
    
public:
    static inline PlatformManager* Get()
    {
        if (!s_PlatformManager)
            s_PlatformManager = new PlatformManager;

        return s_PlatformManager;
    }


    IWindow* CreateWindow(const int Width, const int Height, const char *WindowName);
    void DestroyWindow(IWindow *Window);

    void InitializeOpenGLContext(IWindow *Window) final;
    void MakeContextCurrent(IWindow* Window) final;
    inline FOpenGL* GetOpenGL() final
    {
        return &m_OpenGL;
    };
    
    uint32 GetNumberOfProcessors();

    ISystem* LoadSystem(ESystemType SystemType, IWindow* Window);
    void UnloadSystem(ISystem** System);
    
    //NOTE(EVERYONE): Returns the thread id of the thread that called this funciton
    uint32 GetCallingThreadID();
    
    template <typename T>
    FThread<T> *CreateThread(T *Object, int (T::*Method)(void));

    template <typename T>
    void DestroyThread(FThread<T> *Thread);

    ~PlatformManager() {}

public:
    virtual FHighResolutionTimer CreateHighResolutionTimer() final;
    virtual IMutex* CreateMutex() final;
    virtual void DestroyMutex(IMutex* Mutex) final;
    virtual ISemaphore* CreateSemaphore(int InitialCount) final;
    virtual void DestroySemaphore(ISemaphore* Semaphore) final;
};

#define PLATFORMMANAGER_H
#endif
