TaskManager* TaskManager::s_TaskManager = nullptr;

TaskManager::TaskManager() : m_CompletionGoal(0), m_CompletionCount(0)
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
    if(m_Mutex->TryLock())
    {
        if(!m_Tasks.empty())
        {
            
            const ITask* Task = m_Tasks.front();
            m_Tasks.pop();
            Task->Execute();
            m_CompletionCount++;
        }
        else
        {
            Result = false;
        }
        m_Mutex->Unlock();                        
    }

    return Result;
}

void TaskManager::SubmitTask(const ITask* Task)
{
    m_Mutex->Lock();
    m_CompletionGoal++;
    m_Tasks.push(Task);
    m_Semaphore->Post();
    m_Mutex->Unlock();
}

void TaskManager::CompleteAllSubmittedTasks()
{    
    while(m_CompletionGoal != m_CompletionCount)
    {
        ProcessTask();
    }

    m_CompletionCount = 0;
    m_CompletionGoal = 0;
}
