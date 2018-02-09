#define CLOCK_PRECISION 1E9

static uint64 MacOS_clock()
{
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    uint64 Result = now.tv_sec + now.tv_nsec;
    return Result;
}

static double MacOS_GetElapsedTime(uint64 EndCounter, uint64 StartCounter)
{
    return (EndCounter - StartCounter) / CLOCK_PRECISION;
}

FHighResolutionTimer PlatformManager::CreateHighResolutionTimer() 
{
    FHighResolutionTimer Timer; 
    Timer.StartTimer = MacOS_Clock;
    Timer.EndTimer = MacOS_Clock;
    Timer.ElapsedTime = MacOS_GetElapsedTime;
    return Timer;
}
