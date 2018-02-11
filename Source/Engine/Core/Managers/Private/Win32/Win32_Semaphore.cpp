/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
//NOTE(EVERYONE): Ideally the max count should be number of threads,
//but in posix you cannot specify the max amount. So therefore I need a stub
#define MAX_SEMAPHORE_COUNT 2048

class Win32_Semaphore : public ISemaphore
{
private:
    HANDLE m_Semaphore;
public:
    Win32_Semaphore(int InitialCount);
    void Post() final;
    void Wait() final;
    ~Win32_Semaphore();
};

Win32_Semaphore::Win32_Semaphore(int InitialCount)
{
    m_Semaphore = CreateSemaphore(nullptr, InitialCount, MAX_SEMAPHORE_COUNT, nullptr);
}

void Win32_Semaphore::Post()
{
    ReleaseSemaphore(m_Semaphore, 1, 0);
}

void Win32_Semaphore::Wait()
{
    WaitForSingleObjectEx(m_Semaphore, INFINITE, FALSE);
}

Win32_Semaphore::~Win32_Semaphore()
{
    if(m_Semaphore)
        CloseHandle(m_Semaphore);
}

#undef CreateSemaphore
ISemaphore* PlatformManager::CreateSemaphore(int InitialCount)
{
    ISemaphore* Semaphore = new Win32_Semaphore(InitialCount);
    return Semaphore;
}
