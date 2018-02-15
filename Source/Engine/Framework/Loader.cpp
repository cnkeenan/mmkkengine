/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <Pong.h>

FLoader::FLoader()
{
    //TODO(EVERYONE): Instantiate systems here
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
}
