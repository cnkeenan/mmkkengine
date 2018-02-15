#if !defined(IWIDGETTASK_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class IWidgetTask : public ITask
{
private:
protected:
public:

    ESystemType GetType() final { return ESystemType::WIDGET; }
    virtual void Execute() const = 0;
    virtual ~IWidgetTask() {}
};

#define IWIDGETTASK_H
#endif
