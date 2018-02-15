#if !defined(IGRAPHICSTASK_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class IGraphicsTask : public ITask
{
private:
protected:
public:

    ESystemType GetType() final { return ESystemType::GRAPHICS; }
    virtual void Execute() const = 0;
    virtual ~IGraphicsTask() {}
};

#define IGRAPHICSTASK_H
#endif
