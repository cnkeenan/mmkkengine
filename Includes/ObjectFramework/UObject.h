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
public:

    //NOTE(EVERYONE): Can specifiy nullptr to not create the object 
    UObject(FObjectConstructor* ObjectConstructor);

    virtual void BeginPlay();
    virtual void Tick(float DeltaTime);    
    virtual ~UObject();
};

#define UOBJECT_H
#endif
