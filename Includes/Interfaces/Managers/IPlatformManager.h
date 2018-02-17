#if !defined(IPLATFORMMANAGER_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

struct FHighResolutionTimer
{
    //TODO(EVERYONE): Maybe make these doubles? Check how other platforms work
    typedef uint64 FClock();    
    typedef double FElapsedTime(uint64 EndCounter, uint64 StartCounter);
 
    //NOTE(EVERYONE): We are making these function pointers to not
    //mess with the timing values of the virtual function overhead
    FClock* StartTimer;
    FClock* EndTimer;
    FElapsedTime* ElapsedTime;
};

class IPlatformManager
{
public:

    virtual void InitializeOpenGLContext(class IWindow* Window) = 0;

    //NOTE(EVERYONE): Pass nullptr to unset the context
    virtual void MakeContextCurrent(IWindow* Window) = 0;
    
    virtual FHighResolutionTimer CreateHighResolutionTimer() = 0;
    virtual class IMutex* CreateMutex() = 0;
    virtual void DestroyMutex(IMutex* Mutex) = 0;
    
    //NOTE(EVERYONE): Doubt we will use a semaphore in the systems
    //but just in case you can create one in the interface
    virtual class ISemaphore* CreateSemaphore(int InitialCount) = 0;
    virtual void DestroySemaphore(ISemaphore* Semaphore) = 0;

    virtual class FOpenGL* GetOpenGL() = 0;
};

class IMutex
{
protected:
public:
    virtual bool TryLock() = 0;
    virtual void Lock() = 0;
    virtual void Unlock() = 0;
    virtual ~IMutex() {}
};

class ISemaphore
{
protected:
public:

    //NOTE(EVERYONE): Increments the semaphore count by 1
    virtual void Post() = 0;
    //NOTE(EVERYONE): Decrements the semaphore count by 1
    virtual void Wait() = 0;
    virtual ~ISemaphore() {}
};

class IWindow
{
protected:
    
public:
    virtual void Initialize(const int Width, const int Height, const char* WindowName) = 0;
    
    //NOTE(EVERYONE): Returns true if a quit message has been sent, false otherwise          
    virtual void ProcessOSWindowMessages() = 0;
    virtual void SwapOpenGLBuffers() = 0;
    virtual ~IWindow(){} //TODO: windows should define a destructor
};

#define IPLATFORMMANAGER_H
#endif
