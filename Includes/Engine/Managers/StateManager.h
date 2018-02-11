#if !defined(STATEMANAGER_H)

#include <Interfaces/Managers/IStateManager.h>
#include <Interfaces/Observer/IObserver.h>

struct FSubjectObserverList
{
    FSubject* Subject;
    std::vector<IObserver*> Observers;
    std::deque<const FEvent*> EventQueue;
};

class StateManager : public IStateManager, public IObserver
{
private:

    static StateManager* s_SceneStateManager;
    static StateManager* s_ObjectStateManager;

    std::vector<FSubjectObserverList> m_SubjectObserverList;
public:
    static inline StateManager* GetSceneStateManager()
    {
        if(!s_SceneStateManager)
            s_SceneStateManager = new StateManager;

        return s_SceneStateManager;
    }

    static inline StateManager* GetObjectStateManager()
    {
        if(!s_ObjectStateManager)
            s_ObjectStateManager = new StateManager;

        return s_ObjectStateManager;
    }
    
    void Observe(IObserver* Observer, FSubject* Subject);
    virtual void OnEvent(FSubject* Subject, const FEvent* Event) final;

    void Dispatch();
};

#define STATEMANAGER_H
#endif
