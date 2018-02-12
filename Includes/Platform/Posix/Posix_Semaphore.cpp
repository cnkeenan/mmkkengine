class Posix_Semaphore : public ISemaphore
{
    private:
        sem_t m_Semaphore;
    public:
        Posix_Semaphore(int InitialCount);
        void Post() final;
        void Wait() final;
        ~Posix_Semaphore();
};

Posix_Semaphore::Posix_Semaphore(int InitialCount)
{
    sem_init(&m_Semaphore, 0, InitialCount);
}

void Posix_Semaphore::Post()
{
    sem_post(&m_Semaphore);
}

void Posix_Semaphore::Wait()
{
    sem_wait(&m_Semaphore);
}

Posix_Semaphore::~Posix_Semaphore()
{
    sem_destroy(&m_Semaphore);
}

#undef CreateSemaphore
ISemaphore* PlatformManager::CreateSemaphore(int InitialCount)
{
    ISemaphore* Semaphore = new Posix_Semaphore(InitialCount);
    return Semaphore;
}
