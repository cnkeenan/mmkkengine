#if !defined(IPLATFORMMANAGER_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class IPlatformManager
{
public:
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
