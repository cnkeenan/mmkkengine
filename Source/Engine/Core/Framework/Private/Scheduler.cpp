void FScheduler::Init(double Frequency)
{
    m_MasterClock = PlatformManager::Get()->CreateHighResolutionTimer();
    m_Frequency = Frequency;
    m_Lag = 0.0;
    m_StartTimer = m_MasterClock.StartTimer();
    m_DistributionOrder = EDistributeOrder::ASCENDING;
}

double FScheduler::Tick()
{
    double Result = 0.0f;
    do
    {
        uint64 EndTimer = m_MasterClock.EndTimer();
        Result = m_MasterClock.ElapsedTime(EndTimer, m_StartTimer);                        
    } while(Result < m_Frequency);        
    m_StartTimer = m_MasterClock.StartTimer();    

    TaskManager* TaskSubmitter = TaskManager::Get();
    
    //NOTE(EVERYONE): Reversing the order of the tasks could make it more cache friendly for memory
    if(m_DistributionOrder == EDistributeOrder::ASCENDING)
    {        
        m_DistributionOrder = EDistributeOrder::DESCENDING;
    }
    else
    {   
        m_DistributionOrder = EDistributeOrder::ASCENDING;
    }
    
    
    return Result;
}
