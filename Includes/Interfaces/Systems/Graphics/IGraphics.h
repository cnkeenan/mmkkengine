#if !defined(IGRAPHICS_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
class IGraphics : public ISystem
{
private:
protected:
public:

    virtual IGraphicsScene* CreateScene() = 0;
    virtual void DestroyScene(IGraphicsScene** Scene) = 0;     
    ESystemType GetType() final { return ESystemType::GRAPHICS; }
    virtual ~IGraphics() {}
};

typedef IGraphics*
fp_CreateGraphicsSystem(class FLogger* Logger,
                        class IMemoryManager* MemoryManager,
                        class IPlatformManager* PlatformManager,
                        class IWindow* Window);
typedef void fp_DestroyGraphicsSystem(IGraphics** System);

#define IGRAPHICS_H
#endif
