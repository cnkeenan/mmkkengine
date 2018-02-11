#define CLOCK_PRECISION 1E9

static uint64 Posix_Clock()
{
#if OS_LINUX
#define CLOCK_TYPE CLOCK_MONOTONIC_RAW
#elif OS_MAC
#define CLOCK_TYPE CLOCK_MONOTONIC
#endif
    struct timespec now;
    clock_gettime(CLOCK_TYPE, &now);
    uint64 Result = now.tv_sec + now.tv_nsec;
    return Result;
}

static double Posix_GetElapsedTime(uint64 EndCounter, uint64 StartCounter)
{
    return (EndCounter - StartCounter) / CLOCK_PRECISION;
}

FHighResolutionTimer PlatformManager::CreateHighResolutionTimer() 
{
    FHighResolutionTimer Timer; 
    Timer.StartTimer = Posix_Clock;
    Timer.EndTimer = Posix_Clock;
    Timer.ElapsedTime = Posix_GetElapsedTime;
    return Timer;
}

// TODO: not sure why this is being undeffed
#undef GetCurrentTime
char* PlatformManager::GetCurrentTime(char* Result)
{
    //const std::string res = "UNIMPLEMENTED";
    const char* cstr = "UNIMPLEMENTED";
    return (char*)cstr; 
}

