#define CLOCK_PRECISION 1E9
static fclock_t Posix_Clock()
{
#if OS_LINUX
#define CLOCK_TYPE CLOCK_MONOTONIC_RAW
#elif OS_MAC
#define CLOCK_TYPE CLOCK_MONOTONIC
#endif
    struct timespec now;
    clock_gettime(CLOCK_TYPE, &now);
    return now;
}

static double Posix_GetElapsedTime(fclock_t EndCounter, fclock_t StartCounter)
{
    struct timespec End = EndCounter;
    struct timespec Start = StartCounter;
    double Result = ((End.tv_sec - Start.tv_sec)*1000) + ((End.tv_nsec - Start.tv_nsec)/1000000.0);
    return Result;
}

FHighResolutionTimer PlatformManager::CreateHighResolutionTimer() 
{
    FHighResolutionTimer Timer; 
    Timer.StartTimer = Posix_Clock;
    Timer.EndTimer = Posix_Clock;
    Timer.ElapsedTime = Posix_GetElapsedTime;
    return Timer;
}

#undef GetCurrentTime
char* PlatformManager::GetCurrentTime(char* Result)
{
    static fclock_t First = Posix_Clock();
    fclock_t Timed = Posix_Clock();
    double Elapsed = Posix_GetElapsedTime(Timed, First);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    sprintf(Result, "%d:%d:%d.%d", tm.tm_hour, tm.tm_min, tm.tm_sec, (int)Elapsed % 1000);
    return Result; 
}

