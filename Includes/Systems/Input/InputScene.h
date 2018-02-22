#if !defined(INPUTSCENE_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class InputScene : public IInputScene
{
private:
    InputTask m_Task;
    static const ptr_size NUMBER_OF_OBJECTS=64;
    TObjectPool<InputObject> m_ObjectPool;    
protected:
public:

    InputScene();
        
    IInputObject* CreateObject() final;
    void DestroyObject(IInputObject* Object) final;        
        
    void BeginPlay() final;
    void Tick(float DeltaTime) final;
    ITask* GetTask() final;
    
    ~InputScene();
};

#define INPUTSCENE_H
#endif
