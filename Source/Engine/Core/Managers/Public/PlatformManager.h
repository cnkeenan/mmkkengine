#if !defined(PLATFORMMANAGER_H)
#include <Managers/IPlatformManager.h>

#if defined(OS_WINDOWS)
//NOTE(EVERYONE): The reason for these includes is because opengl needs to be included after windows.h
//To fix these random includes we need to recreate gl.h soooo...
//TODO(EVERYONE): Recreate gl.h 

#endif

enum class EConsoleColor
{
    RED,
    GREEN,
    BLUE,
    BLACK,
    WHITE
};

class PlatformManager : public IPlatformManager
{
private:

    static PlatformManager* s_PlatformManager;
    
public:

    static PlatformManager* Get()
    {
        if(!s_PlatformManager)
            s_PlatformManager = new PlatformManager;

        return s_PlatformManager;
    }

    IWindow* CreateWindow(const int Width, const int Height, const char* WindowName);
    void DestroyWindow(IWindow* Window);
    void InitializeOpenGLContext(IWindow* Window);

    static void ChangeConsoleColor(EConsoleColor BackgroundColor, EConsoleColor ForegroundColor);
    static char* GetCurrentTime(char* Buffer);
    
    virtual FHighResolutionTimer CreateHighResolutionTimer() final;
};

#define PLATFORMMANAGER_H
#endif
