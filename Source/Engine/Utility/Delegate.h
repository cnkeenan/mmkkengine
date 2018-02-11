#if !defined(DELEGATE_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

template <typename ReturnType, typename... Params>
class FDelegate
{
private:
    typedef ReturnType (*Method)(void* Object, Params...);
    void* m_Object;
    Method m_Method;
    
public:

    FDelegate(void* Object, Method Method) : m_Object(Object), m_Method(Method)
    {
    }

    template <typename T, ReturnType (T::*TMethod)(Params...)>
    static FDelegate Bind(T* Object)
    {
        return FDelegate(Object, &Function<T, TMethod>);
    }

    ReturnType operator()(Params... arg) const
    {
        return (*m_Method)(m_Object, arg...);
    }

private:
    template <typename T, ReturnType(T::*TMethod)(Params...)>
    static ReturnType Function(void* Object, Params... arg)
    {
        T* ObjectType = (T*)(Object);
        return (ObjectType->*TMethod)(arg...);
    }
};

#define DELEGATE_H
#endif
