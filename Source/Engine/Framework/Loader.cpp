/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <Pong.h>

FLoader::FLoader()
{
}

void FLoader::Initialize(IWindow* Window)
{
    //TODO(EVERYONE): Instantiate systems here
    PlatformManager* Platform = PlatformManager::Get();
    m_AI = (IAI*)Platform->LoadSystem(ESystemType::AI, Window);
    m_Collision = (ICollision*)Platform->LoadSystem(ESystemType::COLLISION, Window);
    m_Graphics = (IGraphics*)Platform->LoadSystem(ESystemType::GRAPHICS, Window);
    m_Input = (IInput*)Platform->LoadSystem(ESystemType::INPUT, Window);
    m_Physics = (IPhysics*)Platform->LoadSystem(ESystemType::PHYSICS, Window);
    m_Sound = (ISound*)Platform->LoadSystem(ESystemType::SOUND, Window);
    m_Transform = (ITransform*)Platform->LoadSystem(ESystemType::TRANSFORM, Window);
    m_Widget = (IWidget*)Platform->LoadSystem(ESystemType::WIDGET, Window);
}

UWorld* FLoader::Load()
{
    UWorld* World = new UWorld;
    World->Initialize(m_AI->CreateScene(), m_Collision->CreateScene(), m_Graphics->CreateScene(),
                      m_Input->CreateScene(), m_Physics->CreateScene(), m_Sound->CreateScene(),
                      m_Transform->CreateScene(), m_Widget->CreateScene());
    FObjectConstructor* ObjectConstructor = World->GetObjectConstructor();    

    World->AddObject(new UBall(ObjectConstructor));

    UPawn* Pawn1 = new UPlayerPaddle(ObjectConstructor);
    Pawn1->ChangeController(new UPongPlayerController(ObjectConstructor));
    World->AddObject(Pawn1);

    UPawn* Pawn2 = new UAIPaddle(ObjectConstructor);
    Pawn2->ChangeController(new UPongAIController(ObjectConstructor));
    World->AddObject(Pawn2);

    World->RemoveObject((UObject**)&Pawn1);

    return World;
}

void FLoader::Unload(UWorld* World)
{    
    World->Destroy(m_AI, m_Collision, m_Graphics, m_Input, m_Physics, m_Sound, m_Transform, m_Widget);                        
    delete World;    
}

FLoader::~FLoader()
{
    //TODO(EVERYONE): Destroy systems here
    PlatformManager* Platform = PlatformManager::Get();
    Platform->UnloadSystem((ISystem**)&m_Widget);
    Platform->UnloadSystem((ISystem**)&m_Transform);
    Platform->UnloadSystem((ISystem**)&m_Sound);
    Platform->UnloadSystem((ISystem**)&m_Physics);
    Platform->UnloadSystem((ISystem**)&m_Input);
    Platform->UnloadSystem((ISystem**)&m_Graphics);
    Platform->UnloadSystem((ISystem**)&m_Collision);
    Platform->UnloadSystem((ISystem**)&m_AI);
}
