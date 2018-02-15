#if !defined(AIOBJECT_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class AIObject : public IAIObject
{
private:
protected:
public:

    void Create();
    void Destroy();
    
    void BeginPlay() final;
    void Tick(float DeltaTime) final;
    ~AIObject() {}
};

#define AIOBJECT_H
#endif
