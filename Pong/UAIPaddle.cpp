/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

UAIPaddle::UAIPaddle(FObjectConstructor* ObjectConstructor) : UPawn(ObjectConstructor)
{}

void UAIPaddle::BeginPlay()
{
    UPawn::BeginPlay();
}

void UAIPaddle::Tick(float DeltaTime)
{
    UPawn::Tick(DeltaTime);
}

UAIPaddle::~UAIPaddle()
{
}

UPongAIController::UPongAIController(FObjectConstructor* ObjectConstructor) : UAIController(ObjectConstructor)
{}

void UPongAIController::BeginPlay()
{
    UAIController::BeginPlay();
}

void UPongAIController::Tick(float DeltaTime)
{
    UAIController::Tick(DeltaTime);
}

UPongAIController::~UPongAIController()
{
}
