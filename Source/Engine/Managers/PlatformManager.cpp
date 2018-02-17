#if OS_WINDOWS
#include <Platform/Win32.h>
#elif OS_MAC
#include <Platform/MacOS.h>
#elif OS_LINUX
#include <Platform/Linux.h>
#endif

#if POSIX
#include <Platform/Posix.h>
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
#else
    return nullptr;
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

void PlatformManager::DestroyMutex(IMutex* Mutex)
{
    if(Mutex)
        delete Mutex;
}

void PlatformManager::DestroySemaphore(ISemaphore* Semaphore)
{
    if(Semaphore)
        delete Semaphore;
}
