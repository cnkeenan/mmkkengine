/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class Win32_Mutex : public IMutex
{
private:
    CRITICAL_SECTION m_CriticalSection;
public:
    Win32_Mutex();

    virtual bool TryLock() final;
    virtual void Lock() final;
    virtual void Unlock() final;
    
    ~Win32_Mutex();
};

Win32_Mutex::Win32_Mutex()
{
    InitializeCriticalSection(&m_CriticalSection);
}

bool Win32_Mutex::TryLock()
{
    bool Result = TryEnterCriticalSection(&m_CriticalSection);
    return Result;
}

void Win32_Mutex::Lock()
{
    EnterCriticalSection(&m_CriticalSection);
}

void Win32_Mutex::Unlock()
{
    LeaveCriticalSection(&m_CriticalSection);
}

Win32_Mutex::~Win32_Mutex()
{
    DeleteCriticalSection(&m_CriticalSection);
}

#undef CreateMutex
IMutex* PlatformManager::CreateMutex()
{
    IMutex* Mutex = new Win32_Mutex;
    return Mutex;
}
