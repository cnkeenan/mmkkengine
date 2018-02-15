/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
UPawn::UPawn(FObjectConstructor* ObjectConstructor) : UActor(ObjectConstructor),
                                                      m_Controller(nullptr)
{}

void UPawn::BeginPlay()
{
    UActor::BeginPlay();
    if(m_Controller)
        m_Controller->BeginPlay();
}

void UPawn::Tick(float DeltaTime)
{
    UActor::Tick(DeltaTime);
    if(m_Controller)
        m_Controller->Tick(DeltaTime);
}

void UPawn::ChangeController(UController* Controller)
{
    if(m_Controller)
    {
        delete m_Controller;
        m_Controller = nullptr;
    }

    m_Controller = Controller;
}

UPawn::~UPawn()
{
    if(m_Controller)
    {
        delete m_Controller;
        m_Controller = nullptr;
    }
}
