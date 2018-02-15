/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

UPlayerPaddle::UPlayerPaddle(FObjectConstructor* ObjectConstructor) : UPawn(ObjectConstructor)
{}

void UPlayerPaddle::BeginPlay()
{
    UPawn::BeginPlay();
}

void UPlayerPaddle::Tick(float DeltaTime)
{
    UPawn::Tick(DeltaTime);
}

UPlayerPaddle::~UPlayerPaddle()
{
}

UPongPlayerController::UPongPlayerController(FObjectConstructor* ObjectConstructor) : UPlayerController(ObjectConstructor)
{}

void UPongPlayerController::BeginPlay()
{
    UPlayerController::BeginPlay();
}

void UPongPlayerController::Tick(float DeltaTime)
{
    UPlayerController::Tick(DeltaTime);
}

void UPongPlayerController::SetupInput()
{
}

UPongPlayerController::~UPongPlayerController()
{
}
