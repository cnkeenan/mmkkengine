#if !defined(SERVICEMANAGER_H)
#include <Interfaces/Managers/IServiceManager.h>

class ServiceManager : public IServiceManager
{
private:

    static ServiceManager* s_ServiceManager;
public:

    static inline ServiceManager* Get()
    {
        if(!s_ServiceManager)
            s_ServiceManager = new ServiceManager;
        return s_ServiceManager;
    }
};

#define SERVICEMANAGER_H
#endif
