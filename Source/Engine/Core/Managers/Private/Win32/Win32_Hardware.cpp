/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
uint32 PlatformManager::GetNumberOfProcessors()
{
    DWORD Result = 0;
    GetLogicalProcessorInformation(nullptr, &Result);
    return Result;
}
