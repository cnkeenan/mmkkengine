#if !defined(UAICONTROLLER_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class OBJECTFRAMEWORK_API UAIController : public UController
{
private:
    class IAIObject* m_AIObject;
public:
    UAIController(FObjectConstructor* ObjectConstructor);
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    ~UAIController();
};

#define UAICONTROLLER_H
#endif
