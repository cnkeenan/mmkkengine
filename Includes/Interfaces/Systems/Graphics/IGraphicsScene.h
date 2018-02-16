#if !defined(IGRAPHICSSCENE_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class IGraphicsScene : public IScene
{
private:
protected:
public:
            
    virtual IGraphicsObject* CreateObject() = 0;
    virtual void DestroyObject(IGraphicsObject* Object) = 0;        
    
    ESystemType GetType() final { return ESystemType::GRAPHICS; }
    virtual void BeginPlay() = 0;
    virtual void Tick(float DeltaTime) = 0;
    virtual ITask* GetTask() = 0;
    
    virtual ~IGraphicsScene() {}
};

#define IGRAPHICSSCENE_H
#endif
