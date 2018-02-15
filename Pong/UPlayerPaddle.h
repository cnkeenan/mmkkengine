#if !defined(UPLAYERPADDLE_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class PONG_API UPlayerPaddle : public UPawn
{
public:
    UPlayerPaddle(FObjectConstructor* ObjectConstructor);

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    
    ~UPlayerPaddle();
};

class PONG_API UPongPlayerController : public UPlayerController
{
public:
    UPongPlayerController(FObjectConstructor* ObjectConstructor);
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void SetupInput() override;
    ~UPongPlayerController();
};


#define UPLAYERPADDLE_H
#endif
