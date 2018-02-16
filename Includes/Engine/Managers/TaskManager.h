#if !defined(TASKMANAGER_H)
#include <Interfaces/Managers/ITaskManager.h>
#include "Thread.h"

class TaskManager : public ITaskManager
{
private:
    std::vector<FThread<TaskManager>*> m_Threads;
    std::queue<const ITask*> m_Tasks;
    ISemaphore* m_Semaphore;
    IMutex* m_Mutex;
    uint32 m_CompletionGoal;
    uint32 m_CompletionCount;

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

    bool ProcessTask();
    void SubmitTask(const ITask* Task);
    void CompleteAllSubmittedTasks();
    
    ~TaskManager();
};

#define TASKMANAGER_H
#endif
