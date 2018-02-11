#if !defined(THREAD_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */ 
template <class T>
class FThread
{
protected:
    typedef int (T::* FMethod)(void);
    T* m_Object;
    FMethod m_Method;

#if OS_WINDOWS
    static uint32 Run(void* Data);
#else 
    static void* Run(void* Data);
#endif

public:
    FThread(T* Object, FMethod Method);        
    virtual void Start() = 0;
    virtual void Stop() = 0;

    virtual ~FThread();
};

#define THREAD_H
#endif
