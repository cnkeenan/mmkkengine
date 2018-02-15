#if !defined(IGRAPHICS_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
class IGraphics : public ISystem
{
private:
protected:
public:

    ESystemType GetType() final { return ESystemType::GRAPHICS; }
    virtual ~IGraphics() {}
};

#define IGRAPHICS_H
#endif
