uint32 PlatformManager::GetNumberOfProcessors()
{
    //TODO: add log statement here
    return sysconf(_SC_NPROCESSORS_ONLN);
}

