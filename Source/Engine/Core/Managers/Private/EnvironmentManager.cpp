EnvironmentManager* EnvironmentManager::s_EnvironmentManager = nullptr;

EnvironmentManager::EnvironmentManager()
{
    //NOTE(EVERYONE): Constructor sets the default values in the manager
    ExecutionState(EExecutionState::RUN);
}

const EExecutionState EnvironmentManager::ExecutionState() const
{
    return m_ExecutionState;
}

void EnvironmentManager::ExecutionState(const EExecutionState ExecutionState)
{
    m_ExecutionState = ExecutionState;
}
