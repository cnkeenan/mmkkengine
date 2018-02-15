#if !defined(UPLAYERCONTROLLER_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class OBJECTFRAMEWORK_API UPlayerController : public UController
{
private:
    class IInputObject* m_InputObject;
public:
    UPlayerController(FObjectConstructor* ObjectConstructor);
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void SetupInput();
    ~UPlayerController();
};

#define UPLAYERCONTROLLER_H
#endif
