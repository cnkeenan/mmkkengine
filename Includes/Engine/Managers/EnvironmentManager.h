#if !defined(ENVIRONMENTMANAGER_H)
#include <Interfaces/Managers/IEnvironmentManager.h>

//TODO(EVERYONE): Handle more execution status's like pause, next scene etc.
enum class EExecutionState
{
    RUN,
    PAUSE,
    NEW_SCENE,
    EXIT
};

//NOTE(EVERYONE): This manager just holds member variables and provides setters and getters on
//these variables
class EnvironmentManager : public IEnvironmentManager
{
private:

    EExecutionState m_ExecutionState;
    
    static EnvironmentManager* s_EnvironmentManager;

    EnvironmentManager();
public:

    static inline EnvironmentManager* Get()
    {
        if(!s_EnvironmentManager)
            s_EnvironmentManager = new EnvironmentManager;
        return s_EnvironmentManager;
    }

    inline const EExecutionState ExecutionState() const;
    inline void ExecutionState(const EExecutionState ExecutionState);
};

#define ENVIRONMENTMANAGER_H
#endif
