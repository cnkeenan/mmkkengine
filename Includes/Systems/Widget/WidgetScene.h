#if !defined(WIDGETSCENE_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class WidgetScene : public IWidgetScene
{
private:
    WidgetTask m_Task;
    static const ptr_size NUMBER_OF_OBJECTS=64;
    FPool* m_ObjectPool;

protected:
public:

    WidgetScene();
        
    IWidgetObject* CreateObject() final;
    void DestroyObject(IWidgetObject* Object) final;        
        
    void BeginPlay() final;
    void Tick(float DeltaTime) final;
    ITask* GetTask() final;
    
    ~WidgetScene();
};

#define WIDGETSCENE_H
#endif
