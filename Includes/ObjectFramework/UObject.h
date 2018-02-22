#if !defined(UOBJECT_H)

class UObject;

template <typename T>
inline T* Cast(UObject* Object)
{
    T* Result = dynamic_cast<T*>(Object);    
    return Result;
}

//NOTE(EVERYONE): The UObject handles all base interact with the engine
class OBJECTFRAMEWORK_API UObject
{    
private:
    
protected:
    FObjectConstructor* m_ObjectConstructor;
    bool m_IsSceneDead;

    
public:

    UObject() {}
    //NOTE(EVERYONE): Can specifiy nullptr to not create the object 
    UObject(FObjectConstructor* ObjectConstructor);

    void operator delete(void* Object, bool IsSceneDead);
    void operator delete(void* Object);

        
    inline virtual void SetIsSceneDead(bool IsSceneDead)
    {
        m_IsSceneDead = IsSceneDead;
    }

    
    virtual void BeginPlay();
    virtual void Tick(float DeltaTime);    
    virtual ~UObject();
};

#define UOBJECT_H
#endif
