#if OS_WINDOWS
#include "Win32/Win32_Window.cpp"
#include "Win32/Win32_OpenGL.cpp"
#include "Win32/Win32_Timer.cpp"
#include "Win32/Win32_Console.cpp"
#include "Win32/Win32_Thread.cpp"
#include "Win32/Win32_Hardware.cpp"
#elif OS_MAC
#elif OS_LINUX
#include "Linux/Linux_Window.cpp"
#include "Linux/Linux_OpenGL.cpp"
#include "Linux/Linux_Timer.cpp"
#endif

PlatformManager* PlatformManager::s_PlatformManager = nullptr;


template <typename T>
#if OS_WINDOWS
uint32 FThread<T>::Run(void* Data)
#else 
void* FThread<T>::Run(void* Data)
#endif
{
    FThread<T>* Thread = (FThread<T>*)Data;
    //NOTE(EVERYONE): The ugly side of c++. This is just calling the binded method 
    int ReturnCode = (Thread->m_Object->*Thread->m_Method)();
#if OS_WINDOWS
    return ReturnCode;
#endif
}


// TODO: probably should make this os specific
template <class T>
FThread<T>::FThread(T* Object, FMethod Method) : m_Object(Object), m_Method(Method)
{}

template <class T>
FThread<T>::~FThread()
{}

void PlatformManager::DestroyWindow(IWindow* Window)
{
    if(Window)    
        delete Window;    
}

template <typename T>
void PlatformManager::DestroyThread(FThread<T>* Thread)
{
    if(Thread)
        delete Thread;
}

