#if !defined(IAISCENE_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class IAIScene : public IScene
{
private:
protected:
public:

    virtual IAIObject* CreateObject() = 0;
    virtual void DestroyObject(IAIObject** Object) = 0;
    
    ESystemType GetType() final { return ESystemType::AI; }
    virtual void BeginPlay() = 0;
    virtual void Tick(float DeltaTime) = 0;
    virtual ITask* GetTask() = 0;
    
    virtual ~IAIScene() {}
};

#define IAISCENE_H
#endif
