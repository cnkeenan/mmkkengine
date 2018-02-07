#if !defined(PLATFORMMANAGER_H)
#include <Managers/IPlatformManager.h>
 
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
