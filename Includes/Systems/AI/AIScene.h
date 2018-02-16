#if !defined(AISCENE_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class AIScene : public IAIScene
{
private:

    AITask m_Task;
    static const ptr_size NUMBER_OF_OBJECTS=64;
    FPool* m_ObjectPool;
    
protected:
public:

    AIScene();

    IAIObject* CreateObject() final;
    void DestroyObject(IAIObject* Object) final;
    
    
    void BeginPlay() final;
    void Tick(float DeltaTime) final;
    ITask* GetTask() final;
    
    ~AIScene();
};

#define AISCENE_H
#endif
