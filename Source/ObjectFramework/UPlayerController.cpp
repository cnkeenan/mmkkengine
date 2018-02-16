/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
UPlayerController::UPlayerController(FObjectConstructor* ObjectConstructor) : UController(ObjectConstructor)
{
    m_InputObject = m_ObjectConstructor->Construct<IInputObject>();    
}

void UPlayerController::BeginPlay()
{
    UController::BeginPlay();    
}

void UPlayerController::Tick(float DeltaTime)
{
    UController::Tick(DeltaTime);    
}

void UPlayerController::SetupInput()
{
}

UPlayerController::~UPlayerController()
{
    m_ObjectConstructor->Destruct((IObject*)m_InputObject);
}
