#if !defined(GRAPHICSOBJECT_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class GraphicsObject : public IGraphicsObject
{
private:
    bool m_IsInitialized;
protected:
public:

    void Create();
    void Destroy();
    
    void BeginPlay() final;
    void Tick(float DeltaTime) final;
    bool IsInitialized() final;
    void* operator new(size_t Size);
    void operator delete(void* Object);
    ~GraphicsObject() {}
};

#define GRAPHICSOBJECT_H
#endif
