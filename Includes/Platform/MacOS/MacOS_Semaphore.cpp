class MacOS_Semaphore : public ISemaphore
{
  private:
    dispatch_semaphore_t m_Semaphore;

  public:
    MacOS_Semaphore(int InitialCount);
    void Post() final;
    void Wait() final;
    ~MacOS_Semaphore();
};

MacOS_Semaphore::MacOS_Semaphore(int InitialCount)
{
    m_Semaphore = dispatch_semaphore_create(InitialCount);
}

void MacOS_Semaphore::Post()
{
    dispatch_semaphore_signal(m_Semaphore);
}

void MacOS_Semaphore::Wait()
{
    dispatch_semaphore_wait(m_Semaphore, DISPATCH_TIME_NOW);
}

MacOS_Semaphore::~MacOS_Semaphore()
{
    dispatch_release(m_Semaphore);
}

#undef CreateSemaphore
ISemaphore *PlatformManager::CreateSemaphore(int InitialCount)
{
    ISemaphore *Semaphore = new MacOS_Semaphore(InitialCount);
    return Semaphore;
}
