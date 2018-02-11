class Posix_Mutex : public IMutex
{
private:
     pthread_mutex_t m_CriticalSection;
public:
    Posix_Mutex();

    virtual bool Lock() final;
    virtual void Unlock() final;
    
    ~Posix_Mutex();
};

bool Posix_Mutex::Lock() {
    int response = pthread_mutex_trylock(&m_CriticalSection);
    if(response == 0) {
        return true;
    }
    else if(response == EBUSY) {
        return false;
    }
    else {
        ASSERT(false);
        return false;
    }

}

void Posix_Mutex::Unlock() {
    if(pthread_mutex_unlock(&m_CriticalSection)) {
        ASSERT(false);
    }
}


#undef CreateMutex
IMutex* PlatformManager::CreateMutex()
{
    IMutex* Mutex = new Posix_Mutex;
    return Mutex;
}