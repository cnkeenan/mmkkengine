#if !defined(IINPUTSCENE_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class IInputScene : public IScene
{
private:
protected:
public:
                
    virtual IInputObject* CreateObject() = 0;
    virtual void DestroyObject(IInputObject** Object) = 0;            
    
    ESystemType GetType() final { return ESystemType::INPUT; }
    virtual void BeginPlay() = 0;
    virtual void Tick(float DeltaTime) = 0;
    virtual ITask* GetTask() = 0;
    
    virtual ~IInputScene() {}
};

#define IINPUTSCENE_H
#endif
