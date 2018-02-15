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
    ESystemType GetType() final { return ESystemType::GRAPHICS; }
    virtual ~IGraphics() {}
};

#define IGRAPHICS_H
#endif
