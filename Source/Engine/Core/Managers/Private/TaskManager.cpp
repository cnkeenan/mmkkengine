TaskManager* TaskManager::s_TaskManager = nullptr;

TaskManager::TaskManager()
{
    m_Threads.resize(PlatformManager::Get()->GetNumberOfProcessors()-1);
    for(auto& Thread : m_Threads)
        Thread = PlatformManager::Get()->CreateThread(this, &TaskManager::ThreadProcedure);
}

TaskManager::~TaskManager()
{
    for(auto& Thread : m_Threads)
        PlatformManager::Get()->DestroyThread(Thread);
}

int TaskManager::ThreadProcedure()
{

    return 0;
}
