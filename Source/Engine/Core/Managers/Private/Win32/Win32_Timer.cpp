/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
static LARGE_INTEGER Global_Frequency;

static uint64 Win32_Clock()
{
    LARGE_INTEGER Counter;
    QueryPerformanceCounter(&Counter);
    return Counter.QuadPart;
}

static double Win32_GetElapsedTime(uint64 EndCounter, uint64 StartCounter)
{
    double Result = (double)(EndCounter-StartCounter)/(double)Global_Frequency.QuadPart;
    return Result;
}

FHighResolutionTimer PlatformManager::CreateHighResolutionTimer()
{
    static bool IsInitialized = false;
    if(!IsInitialized)
    {
        QueryPerformanceFrequency(&Global_Frequency);
        IsInitialized = true;
    }
    FHighResolutionTimer Timer;
    Timer.StartTimer = Win32_Clock;
    Timer.EndTimer = Win32_Clock;
    Timer.ElapsedTime = Win32_GetElapsedTime;
    return Timer;
}
