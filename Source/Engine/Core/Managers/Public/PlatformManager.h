#if !defined(PLATFORMMANAGER_H)
#include <Managers/IPlatformManager.h>

template <typename T>
class FThread;

class PlatformManager : public IPlatformManager
{
private:
    static PlatformManager* s_PlatformManager;
    
public:
    static inline PlatformManager* Get()
    {
        if(!s_PlatformManager)
            s_PlatformManager = new PlatformManager;

        return s_PlatformManager;
    }

    IWindow* CreateWindow(const int Width, const int Height, const char* WindowName);
    void DestroyWindow(IWindow* Window);
    
    void InitializeOpenGLContext(IWindow* Window);
    uint32 GetNumberOfProcessors();

    //NOTE(EVERYONE): Returns the thread id of the thread that called this funciton
    uint32 GetCallingThreadID();
    
    template <typename T>
    FThread<T>* CreateThread(T* Object, int (T::* Method)(void)); 

    template <typename T>
    void DestroyThread(FThread<T>* Thread);
    
    static void ChangeConsoleColor(EConsoleColor BackgroundColor, EConsoleColor ForegroundColor);
    static char* GetCurrentTime(char* Buffer);

public:
    virtual FHighResolutionTimer CreateHighResolutionTimer() final;
    virtual IMutex* CreateMutex() final;
    virtual void DestroyMutex(IMutex* Mutex) final;
    virtual ISemaphore* CreateSemaphore(int InitialCount) final;
    virtual void DestroySemaphore(ISemaphore* Semaphore) final;
};

#define PLATFORMMANAGER_H
#endif
