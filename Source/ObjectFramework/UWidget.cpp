/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

UWidget::UWidget(FObjectConstructor* ObjectConstructor) : UObject(ObjectConstructor)        
{
    m_GraphicsObject = m_ObjectConstructor->Construct<IGraphicsObject>();
    m_WidgetObject = m_ObjectConstructor->Construct<IWidgetObject>();
}

void UWidget::BeginPlay()
{
    UObject::BeginPlay();    
}

void UWidget::Tick(float DeltaTime)
{
    UObject::Tick(DeltaTime);    
}

UWidget::~UWidget()
{
    if(!m_IsSceneDead)
    {
        m_ObjectConstructor->Destruct((IObject*)m_WidgetObject);
        m_ObjectConstructor->Destruct((IObject*)m_GraphicsObject);
    }
}
