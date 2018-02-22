
UObject::UObject(FObjectConstructor* ObjectConstructor) : m_ObjectConstructor(ObjectConstructor)     ,
                                                          m_IsSceneDead(false)
{}

void UObject::BeginPlay()
{
}

void UObject::Tick(float DeltaTime)
{
}

void UObject::operator delete(void* Object, bool IsSceneDead)
{
    UObject* RealObject = (UObject*)Object;
    if(IsSceneDead)
    {
        RealObject->SetIsSceneDead(IsSceneDead);
    }
    delete RealObject;
}

void UObject::operator delete(void* Object)
{
    UObject* RealObject = (UObject*)Object;
    RealObject->~UObject();
    delete Object;    
}

UObject::~UObject()
{
    
}
