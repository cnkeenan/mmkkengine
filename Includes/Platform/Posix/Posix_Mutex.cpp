class Posix_Mutex : public IMutex
{
private:
     pthread_mutex_t m_CriticalSection;
public:
    Posix_Mutex();

    virtual bool TryLock() final;
    virtual void Lock() final;
    virtual void Unlock() final;
    
    ~Posix_Mutex();
};

Posix_Mutex::Posix_Mutex() {}
Posix_Mutex::~Posix_Mutex() {}

bool Posix_Mutex::TryLock() {
    int response = pthread_mutex_trylock(&m_CriticalSection);
    if(response == 0)
    {
        return true;
    }
    else if(response == EBUSY)
    {
        return false;
    }
    else
    {
        ASSERT(false, "Unable to obtain pthread_mutex.");
        return false;
    }

}

void Posix_Mutex::Lock()
{
    pthread_mutex_lock(&m_CriticalSection);
}

void Posix_Mutex::Unlock()
{
    if(pthread_mutex_unlock(&m_CriticalSection) != 0)
    {
        ASSERT(false, "Unable to unlock pthread_mutex");
    }
}


#undef CreateMutex
IMutex* PlatformManager::CreateMutex()
{
    IMutex* Mutex = new Posix_Mutex;
    return Mutex;
}
