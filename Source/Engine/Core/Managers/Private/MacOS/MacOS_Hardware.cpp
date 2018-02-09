
uint32 PlatformManager::GetNumberOfProcessors()
{
    m_logical_processors = 0;
    m_logical_processors = system("../../../processor_posix.sh");

    return m_logical_processors;
}