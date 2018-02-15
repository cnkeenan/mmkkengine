#if !defined(ISOUNDSCENE_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class ISoundScene : public IScene
{
private:
protected:
public:

                        
    virtual ISoundObject* CreateObject() = 0;
    virtual void DestroyObject(ISoundObject** Object) = 0;                

    ESystemType GetType() final { return ESystemType::SOUND; }
    virtual void BeginPlay() = 0;
    virtual void Tick(float DeltaTime) = 0;
    virtual ITask* GetTask() = 0;
    
    virtual ~ISoundScene() {}
};

#define ISOUNDSCENE_H
#endif
