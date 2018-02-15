#if !defined(UACTOR_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class OBJECTFRAMEWORK_API UActor : public UEntity
{
private:
    IGraphicsObject* m_GraphicsObject;

protected:
public:

    UActor(FObjectConstructor* ObjectConstructor);
        
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;    
    
    virtual ~UActor();
};

#define UACTOR_H
#endif
