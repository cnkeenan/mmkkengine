/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include "../../public/Thread.h"

template <class T>
class Win32_Thread : public FThread<T>
{
private:
    HANDLE m_Thread;
    DWORD m_ThreadID;
public:
    Win32_Thread(T* Object, FMethod Method);
    virtual void Start() final;
    virtual void Stop() final;

    ~Win32_Thread();
};

template <class T>
Win32_Thread<T>::Win32_Thread(T* Object, FMethod Method) : FThread(Object, Method)
{
    m_Thread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)FThread<T>::Run, this, CREATE_SUSPENDED, &m_ThreadID);
}

template <class T>
Win32_Thread<T>::~Win32_Thread()
{
    if(m_Thread)
        CloseHandle(m_Thread);
}

template <class T>
void Win32_Thread<T>::Start()
{
    ResumeThread(m_Thread);
}

template <class T>
void Win32_Thread<T>::Stop()
{
    SuspendThread(m_Thread);
}

template <typename T>
FThread<T>* PlatformManager::CreateThread(T* Object, int (T::* Method)(void))
{
    FThread<T>* Result = new Win32_Thread<T>(Object, Method);
    return Result;
}
