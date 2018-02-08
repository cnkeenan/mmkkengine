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

    virtual FHighResolutionTimer CreateHighResolutionTimer() = 0;
};

class IWindow
{
protected:
    
public:
    virtual void Initialize(const int Width, const int Height, const char* WindowName) = 0;
    
    //NOTE(EVERYONE): Returns true if a quit message has been sent, false otherwise          
    virtual bool ProcessOSWindowMessages() = 0;

    virtual void SwapOpenGLBuffers() = 0;
};

#define IPLATFORMMANAGER_H
#endif
