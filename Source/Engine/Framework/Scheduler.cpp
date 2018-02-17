void FScheduler::Init(double Frequency)
{
    m_MasterClock = PlatformManager::Get()->CreateHighResolutionTimer();
    m_Frequency = Frequency;
    m_Lag = 0.0;
    m_StartTimer = m_MasterClock.StartTimer();
    m_DistributionOrder = EDistributeOrder::ASCENDING;    
}

double FScheduler::Tick(UWorld* World)
{
    double Result = 0.0f;
    do
    {
        fclock_t EndTimer = m_MasterClock.EndTimer();
        Result = m_MasterClock.ElapsedTime(EndTimer, m_StartTimer);                        
    } while(Result < m_Frequency);        
    m_StartTimer = m_MasterClock.StartTimer();    

    TaskManager* TaskSubmitter = TaskManager::Get();
    
    //NOTE(EVERYONE): Reversing the order of the tasks could make it more cache friendly for memory
    if(m_DistributionOrder == EDistributeOrder::ASCENDING)
    {
        TaskSubmitter->SubmitTask(World->m_AIScene->GetTask());
        TaskSubmitter->SubmitTask(World->m_CollisionScene->GetTask());
        TaskSubmitter->SubmitTask(World->m_GraphicsScene->GetTask());
        TaskSubmitter->SubmitTask(World->m_InputScene->GetTask());
        TaskSubmitter->SubmitTask(World->m_PhysicsScene->GetTask());
        TaskSubmitter->SubmitTask(World->m_SoundScene->GetTask());
        TaskSubmitter->SubmitTask(World->m_TransformScene->GetTask());
        TaskSubmitter->SubmitTask(World->m_WidgetScene->GetTask());
        
        m_DistributionOrder = EDistributeOrder::DESCENDING;
    }
    else
    {
        TaskSubmitter->SubmitTask(World->m_WidgetScene->GetTask());        
        TaskSubmitter->SubmitTask(World->m_TransformScene->GetTask());
        TaskSubmitter->SubmitTask(World->m_SoundScene->GetTask());
        TaskSubmitter->SubmitTask(World->m_PhysicsScene->GetTask());
        TaskSubmitter->SubmitTask(World->m_InputScene->GetTask());
        TaskSubmitter->SubmitTask(World->m_GraphicsScene->GetTask());
        TaskSubmitter->SubmitTask(World->m_CollisionScene->GetTask());
        TaskSubmitter->SubmitTask(World->m_AIScene->GetTask());
        m_DistributionOrder = EDistributeOrder::ASCENDING;
    }

    return Result;
}

