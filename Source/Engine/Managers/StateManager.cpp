StateManager* StateManager::s_SceneStateManager = nullptr;
StateManager* StateManager::s_ObjectStateManager = nullptr;

void StateManager::Observe(IObserver* Observer, FSubject* Subject)
{
    Subject->AddObserver(this);
    bool Found = false;
    for(auto& SubjectObserver : m_SubjectObserverList)
    {
        if(SubjectObserver.Subject == Subject)
        {            
            for(auto& ListObserver : SubjectObserver.Observers)
            {
                //NOTE(EVERYONE): Make sure we do not allow duplicate observers in the change-controller
                ASSERT(ListObserver != Observer, "Duplicate observers");                                
            }

            SubjectObserver.Observers.push_back(Observer);
            Found = true;            
        }
    }

    if(!Found)
    {

        
        FSubjectObserverList SubjectObserverList;
        SubjectObserverList.Subject = Subject;
        SubjectObserverList.Observers.push_back(Observer);
        m_SubjectObserverList.push_back(SubjectObserverList);
    }
}

void StateManager::OnEvent(FSubject* Subject, const FEvent* Event)
{
    
    for(auto& SubjectObserver : m_SubjectObserverList)
    {
        if(Subject == SubjectObserver.Subject)
        {
            SubjectObserver.EventQueue.push_back(Event);
            break;
        }
    }
}

void StateManager::Dispatch()
{
                
    for(auto& SubjectObserver : m_SubjectObserverList)
    {
        FSubject* Subject = SubjectObserver.Subject;
        const FEvent* Event = SubjectObserver.EventQueue.front();
        SubjectObserver.EventQueue.pop_front();
        
        for(auto& Observer : SubjectObserver.Observers)
        {
            Observer->OnEvent(Subject, Event);
        }
    }
}
