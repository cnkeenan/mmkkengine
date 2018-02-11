#if !defined(TASKMANAGER_H)
#include <Managers/ITaskManager.h>
#include "Thread.h"

class TaskManager : public ITaskManager
{
private:
    std::vector<FThread<TaskManager>*> m_Threads;

    static TaskManager* s_TaskManager;

    TaskManager();
public:
    static inline TaskManager* Get()
    {
        if(!s_TaskManager)
            s_TaskManager = new TaskManager;

        return s_TaskManager;
    }

    int ThreadProcedure();
    ~TaskManager();
};

#define TASKMANAGER_H
#endif
