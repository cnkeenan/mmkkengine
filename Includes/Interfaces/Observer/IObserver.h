#if !defined(IOBSERVER_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class FEvent;

class IObserver
{
public:
    virtual ~IObserver() {}
    virtual void OnEvent(class FSubject* Subject, const FEvent* Event) = 0;
};

class FSubject
{
private:
    std::vector<IObserver*> m_Observers;
public:
    inline void AddObserver(IObserver* Observer)
    {
        bool FoundObserver = false;
        for(auto& ListObserver : m_Observers)
        {
            if(Observer == ListObserver)
            {
                FoundObserver = true;
                break;
            }
        }
        if(!FoundObserver)
            m_Observers.push_back(Observer);
    }

    inline void RemoveObserver(IObserver* Observer)
    {        
        for(uint32 ObserverIndex = 0; ObserverIndex < m_Observers.size(); ObserverIndex++)
        {
            if(m_Observers[ObserverIndex] == Observer)
            {
                m_Observers.erase(m_Observers.begin() + ObserverIndex);
                break;
            }
        }        
    }

protected:
    inline void Notify(const FEvent* Event)
    {
        for(auto& Observer : m_Observers)
        {
            Observer->OnEvent(this, Event);
        }
    }
};


#define IOBSERVER_H
#endif
