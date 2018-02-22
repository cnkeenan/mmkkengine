static fclock_t Posix_Clock()
{

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
