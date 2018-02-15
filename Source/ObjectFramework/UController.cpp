/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
UController::UController(FObjectConstructor* ObjectConstructor) : UObject(ObjectConstructor)
{}

void UController::BeginPlay()
{
    UObject::BeginPlay();
}

void UController::Tick(float DeltaTime)
{
    UObject::Tick(DeltaTime);
}

UController::~UController()
{
}
