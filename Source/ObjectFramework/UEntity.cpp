/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

UEntity::UEntity(FObjectConstructor* ObjectConstructor) : UObject(ObjectConstructor)        
{
    m_TransformObject = m_ObjectConstructor->Construct<ITransformObject>();
    m_CollisionObject = m_ObjectConstructor->Construct<ICollisionObject>();
    m_PhysicsObject = m_ObjectConstructor->Construct<IPhysicsObject>();
    m_SoundObject = m_ObjectConstructor->Construct<ISoundObject>();
}

void UEntity::BeginPlay()
{
    UObject::BeginPlay();    
}

void UEntity::Tick(float DeltaTime)
{
    UObject::Tick(DeltaTime);    
}

UEntity::~UEntity()
{
    m_ObjectConstructor->Destruct((IObject**)&m_SoundObject);
    m_ObjectConstructor->Destruct((IObject**)&m_PhysicsObject);
    m_ObjectConstructor->Destruct((IObject**)&m_CollisionObject);
    m_ObjectConstructor->Destruct((IObject**)&m_TransformObject);
}
