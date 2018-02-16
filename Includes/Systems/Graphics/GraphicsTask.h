#if !defined(GRAPHICSTASK_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class GraphicsTask : public IGraphicsTask
{
private:
protected:
public:

    GraphicsTask();
    void Execute() const final;
    ~GraphicsTask();
};

#define GRAPHICSTASK_H
#endif
