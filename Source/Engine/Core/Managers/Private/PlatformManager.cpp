#if OS_WINDOWS
#include "Win32/Win32_Window.cpp"
#include "Win32/Win32_OpenGL.cpp"
#include "Win32/Win32_Timer.cpp"
#include "Win32/Win32_Console.cpp"
#elif OS_MAC
#elif OS_LINUX
#include "Linux/Linux_Window.cpp"
#include "Linux/Linux_OpenGL.cpp"
#endif

PlatformManager* PlatformManager::s_PlatformManager = nullptr;

// TODO: probably should make this os specific
void PlatformManager::DestroyWindow(IWindow* Window)
{
    if(Window)    
        delete Window;    
}


