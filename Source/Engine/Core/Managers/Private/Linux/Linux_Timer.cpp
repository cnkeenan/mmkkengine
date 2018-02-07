#define CLOCK_PRECISION 1E9

static uint64 Linux_Clock()
{
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    uint64 Result = now.tv_sec + now.tv_nsec;
    return Result;
}

static double Linux_GetElapsedTime(uint64 EndCounter, uint64 StartCounter)
{
    return (EndCounter - StartCounter) / CLOCK_PRECISION;
}

FHighResolutionTimer PlatformManager::CreateHighResolutionTimer() 
{
    FHighResolutionTimer Timer; 
    Timer.StartTimer = Linux_Clock;
    Timer.EndTimer = Linux_Clock;
    Timer.ElapsedTime = Linux_GetElapsedTime;
    return Timer;
}
