#if !defined(TRANSFORMSCENE_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class TransformScene : public ITransformScene
{
private:
    TransformTask m_Task;
    
    static const ptr_size NUMBER_OF_OBJECTS=64;
    FPool* m_ObjectPool;

    
protected:
public:

    TransformScene();
        
    ITransformObject* CreateObject() final;
    void DestroyObject(ITransformObject* Object) final;        
        
    void BeginPlay() final;
    void Tick(float DeltaTime) final;
    ITask* GetTask() final;
    
    ~TransformScene();
};

#define TRANSFORMSCENE_H
#endif
