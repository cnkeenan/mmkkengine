/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
uint32 PlatformManager::GetNumberOfProcessors()
{
    SYSTEM_INFO SystemInfo;
    GetSystemInfo(&SystemInfo);
    return SystemInfo.dwNumberOfProcessors;
}
