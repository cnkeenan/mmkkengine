/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

UActor::UActor(FObjectConstructor* ObjectConstructor) : UEntity(ObjectConstructor)        
{
    m_GraphicsObject = m_ObjectConstructor->Construct<IGraphicsObject>();
}

void UActor::BeginPlay()
{
    UEntity::BeginPlay();    
}

void UActor::Tick(float DeltaTime)
{
    UEntity::Tick(DeltaTime);    
}

UActor::~UActor()
{
    if(m_GraphicsObject)
    {
        m_ObjectConstructor->Destruct((IObject*)m_GraphicsObject);
    }
}
