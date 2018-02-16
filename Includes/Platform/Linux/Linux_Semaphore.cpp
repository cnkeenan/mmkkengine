class Linux_Semaphore : public ISemaphore
{
    private:
        sem_t m_Semaphore;
    public:
        Linux_Semaphore(int InitialCount);
        void Post() final;
        void Wait() final;
        ~Linux_Semaphore();
};

Linux_Semaphore::Linux_Semaphore(int InitialCount)
{
    sem_init(&m_Semaphore, 0, InitialCount);
}

void Linux_Semaphore::Post()
{
    sem_post(&m_Semaphore);
}

void Linux_Semaphore::Wait()
{
    sem_wait(&m_Semaphore);
}

Linux_Semaphore::~Linux_Semaphore()
{
    sem_destroy(&m_Semaphore);
}

#undef CreateSemaphore
ISemaphore* PlatformManager::CreateSemaphore(int InitialCount)
{
    ISemaphore* Semaphore = new Linux_Semaphore(InitialCount);
    return Semaphore;
}
