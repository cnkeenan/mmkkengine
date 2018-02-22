/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
UAIController::UAIController(FObjectConstructor* ObjectConstructor) : UController(ObjectConstructor)
{
    m_AIObject = m_ObjectConstructor->Construct<IAIObject>();
}

void UAIController::BeginPlay()
{
    UController::BeginPlay();    
}

void UAIController::Tick(float DeltaTime)
{
    UController::Tick(DeltaTime);    
}

UAIController::~UAIController()
{
    if(!m_IsSceneDead)
        m_ObjectConstructor->Destruct((IObject*)m_AIObject);
}
