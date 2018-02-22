/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
static LARGE_INTEGER Global_Frequency;
static bool Global_Initialized;

static fclock_t Win32_Clock()
{
    LARGE_INTEGER Counter;
    QueryPerformanceCounter(&Counter);
    return Counter.QuadPart;
}

static double Win32_GetElapsedTime(fclock_t EndCounter, fclock_t StartCounter)
{
    double Result = (double)(EndCounter-StartCounter)/(double)Global_Frequency.QuadPart;
    return Result;
}

FHighResolutionTimer PlatformManager::CreateHighResolutionTimer()
{    
    if(!Global_Initialized)
    {
        QueryPerformanceFrequency(&Global_Frequency);
        Global_Initialized = true;
    }
    FHighResolutionTimer Timer;
    Timer.StartTimer = Win32_Clock;
    Timer.EndTimer = Win32_Clock;
    Timer.ElapsedTime = Win32_GetElapsedTime;
    return Timer;
}
