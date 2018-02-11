TaskManager* TaskManager::s_TaskManager = nullptr;

TaskManager::TaskManager()
{
    PlatformManager* Platform = PlatformManager::Get();
    m_Threads.resize(Platform->GetNumberOfProcessors()-1);


    m_Semaphore = Platform->CreateSemaphore(0);
    m_Mutex = Platform->CreateMutex();
    for(auto& Thread : m_Threads)
    {
        Thread = Platform->CreateThread(this, &TaskManager::ThreadProcedure);
        Thread->Start();
    }
}

TaskManager::~TaskManager()
{
    PlatformManager* Platform = PlatformManager::Get();
        
    for(auto& Thread : m_Threads)
        PlatformManager::Get()->DestroyThread(Thread);
    Platform->DestroyMutex(m_Mutex);
    Platform->DestroySemaphore(m_Semaphore);
}

int TaskManager::ThreadProcedure()
{
    EnvironmentManager* Environment = EnvironmentManager::Get();
    while(Environment->ExecutionState() == EExecutionState::RUN)
    {
        if(!ProcessTask())
        {
            m_Semaphore->Wait();
        }
    }
    return 0;
}

bool TaskManager::ProcessTask()
{
    bool Result = true;
    if(m_Tasks.size() != 0)
    {
        bool HasLock = m_Mutex->Lock();
        if(HasLock)
        {
            const ITask* Task = m_Tasks.front();
            m_Tasks.pop_front();
            Task->Execute();
            m_Mutex->Unlock();
        }
    }
    else
    {
        Result = false;
    }

    return Result;
}

void TaskManager::SubmitTask(const ITask* Task)
{
    m_Tasks.push_back(Task);
    m_Semaphore->Post();
}

void TaskManager::CompleteAllSubmittedTasks()
{
    while(m_Tasks.size() != 0)
    {
        ProcessTask();
    }
}
