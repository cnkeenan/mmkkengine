#include <Engine/Managers/Thread.h>
#include "Posix.h"


//TODO:
//
//Probably best if we have all threads communicate using some shared state
//and synchronized with mutexes. Instead of using pthread_cancel.
//

template <class T>
class Posix_Thread : public FThread<T>
{
    private:
        typedef typename FThread<T>::FMethod FMethod;
        pthread_t m_Thread;
        bool m_ValidThreadInit = false;

    public:
        Posix_Thread(T* Object, FMethod Method);
        virtual void Start() final;
        virtual void Stop() final;

        ~Posix_Thread();
};

template <class T>
Posix_Thread<T>::Posix_Thread(T* Object, FMethod Method) : FThread<T>(Object, Method)
{
    /**
     * Provided definition in order to implement the interface.
     * The thread is already in the ready queue when calling
     * pthread_create if initialization was successful.
     */
}

template <class T>
void Posix_Thread<T>::Start() {
    int res;

    if (m_ValidThreadInit) 
    {
        res = pthread_join(m_Thread, nullptr);
        if (res != 0)
        {
            switch(res)
            {
                case EDEADLK:
                    return;

                default:
                    break;
            }
        }
    }

    res = pthread_create(&m_Thread, NULL, FThread<T>::Run, this);
    if (res == 0) 
    {
        m_ValidThreadInit = true;
    }
    else
    {
        m_ValidThreadInit = false;
        switch(res)
        {
            // BAD ATTRIBUTES
            case EINVAL: 
                break;

            // NO PERMISSIONS FOR SPECIFIED ATTRIBUTES
            case EPERM: 
                break;

            // NOT ENOUGH RESOURCES OR SYS IMPOSED LIMIT
            case EAGAIN: 
                break;

            // SENTINEL
            default: 
                break;
        }
    }


}

template <class T>
void Posix_Thread<T>::Stop()
{
    int res;

    if (m_Thread)
    {
        res = pthread_cancel(m_Thread);
        switch(res)
        {
            case ESRCH: // ID NOT FOUND
                break;
        }
    }
}

template <class T>
Posix_Thread<T>::~Posix_Thread()
{
    if (m_Thread)
    {
        pthread_cancel(m_Thread);
    }
}

template <typename T>
FThread<T>* PlatformManager::CreateThread(T* Object, int (T::* Method)(void))
{
    FThread<T>* Result = new Posix_Thread<T>(Object, Method);
    return Result;
}


