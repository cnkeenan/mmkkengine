#if !defined(UAIPADDLE_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class PONG_API UAIPaddle : public UPawn
{
    UAIPaddle(FObjectConstructor* ObjectConstructor);

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    
    ~UAIPaddle();
};

class PONG_API UPongAIController : public UAIController
{
    UPongAIController(FObjectConstructor* ObjectConstructor);
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    ~UPongAIController();
};

#define UAIPADDLE_H
#endif
