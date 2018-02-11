/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
static LARGE_INTEGER Global_Frequency;
static bool Global_Initialized;

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

#undef GetCurrentTime
char* PlatformManager::GetCurrentTime(char* Result)
{
    if(!Global_Initialized)
    {
        QueryPerformanceFrequency(&Global_Frequency);
        Global_Initialized = true;
    }
    
    char Buffer[128];
    GetTimeFormat(LOCALE_USER_DEFAULT, 0, 0, "HH':'mm':'ss", Buffer, sizeof(Buffer));

    static uint64 First = Win32_Clock();
    uint64 Timed = Win32_Clock();

    uint64 Elapsed = (Timed-First)*1000;
    Elapsed /= Global_Frequency.QuadPart;
    
    sprintf(Result, "%s.%03I64d", Buffer, Elapsed % 1000);
    return Result; 
}
