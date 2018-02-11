#if !defined(EVENTS_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include "Delegate.h"

enum class EEventType
{
    TEST,
    KEY_PRESSED,
    KEY_RELEASED,
    MOUSE_PRESSED,
    MOUSE_RELEASED,
    MOUSE_MOVED
};

#define Dispatch(return_type, event_type, object_name, object, method) \
    Dispatch_<event_type>(FDelegate<return_type, event_type*>::Bind<object_name, &object_name::method>(object))

class FEventDispatcher
{
private:
    class FEvent* m_Event;
public:

    inline FEventDispatcher(FEvent* Event) : m_Event(Event) {}

    template <typename T>
    inline void Dispatch_(FDelegate<bool, T*> Delegate);
};

class FEvent
{
    friend class FEventDispatcher;
protected:
    bool m_Handled;
    EEventType m_Type;

    inline FEvent(EEventType Type) : m_Type(Type), m_Handled(false) {}
public:
    inline EEventType Type() const { return m_Type; }
    inline bool IsHandled() const { return m_Handled; }
};

//NOTE(EVERYONE): ADD EVENTS HERE
//When subclassing events, you must define a static EEventType GetStaticType() 
//that returns the event type. Make sure to add that event type to the Enum at the top of the class

class TestEvent : public FEvent
{

public:
    inline TestEvent(EEventType Type) : FEvent(Type) {}

    static EEventType GetStaticType() { return EEventType::TEST; } 
};

///////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void FEventDispatcher::Dispatch(FDelegate<bool, T*> Delegate)
{
    if((int32)m_Event->Type() == (int32)T::GetStaticType())
        m_Event->m_Handled = Delegate((T*)m_Event);
}


#define EVENTS_H
#endif
