#if OS_WINDOWS
#include "Win32/Win32_Window.cpp"
#include "Win32/Win32_OpenGL.cpp"
#elif OS_MAC
#elif OS_LINUX
#endif

PlatformManager* PlatformManager::s_PlatformManager = nullptr;

void PlatformManager::DestroyWindow(IWindow* Window)
{
    if(Window)    
        delete Window;    
}


