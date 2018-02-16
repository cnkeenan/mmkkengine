#if !defined(ITRANSFORMSCENE_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class ITransformScene : public IScene
{
private:
protected:
public:

                            
    virtual ITransformObject* CreateObject() = 0;
    virtual void DestroyObject(ITransformObject* Object) = 0;                

    ESystemType GetType() final { return ESystemType::TRANSFORM; }
    virtual void BeginPlay() = 0;
    virtual void Tick(float DeltaTime) = 0;
    virtual ITask* GetTask() = 0;
    
    virtual ~ITransformScene() {}
};

#define ITRANSFORMSCENE_H
#endif
