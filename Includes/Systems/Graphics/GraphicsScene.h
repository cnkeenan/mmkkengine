#if !defined(GRAPHICSSCENE_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class GraphicsScene : public IGraphicsScene
{
private:
    GraphicsTask m_Task;
    static const ptr_size NUMBER_OF_OBJECTS=64;
    FPool* m_ObjectPool;    
protected:
public:

    GraphicsScene();
        
    IGraphicsObject* CreateObject() final;
    void DestroyObject(IGraphicsObject* Object) final;        
        
    void BeginPlay() final;
    void Tick(float DeltaTime) final;
    ITask* GetTask() final;
    
    ~GraphicsScene();
};

#define GRAPHICSSCENE_H
#endif
