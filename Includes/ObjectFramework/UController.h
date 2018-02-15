#if !defined(UCONTROLLER_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class OBJECTFRAMEWORK_API UController : public UObject
{
private:
protected:
public:
    UController(FObjectConstructor* ObjectConstructor);
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual ~UController();
};

#define UCONTROLLER_H
#endif
