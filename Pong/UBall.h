#if !defined(UBALL_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
class PONG_API UBall : public UActor
{
public:
private:
    UBall(FObjectConstructor* ObjectConstructor);

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    ~UBall();
};

#define UBALL_H
#endif
