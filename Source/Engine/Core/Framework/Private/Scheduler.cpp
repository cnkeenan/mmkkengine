void FScheduler::Init(double Frequency)
{
    m_MasterClock = PlatformManager::Get()->CreateHighResolutionTimer();
    m_Frequency = Frequency;
    m_Lag = 0.0;
    m_StartTimer = m_MasterClock.StartTimer();    
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
    return Result;
}
