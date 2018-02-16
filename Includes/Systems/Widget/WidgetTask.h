#if !defined(WIDGETTASK_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class WidgetTask : public IWidgetTask
{
private:
protected:
public:

    WidgetTask();
    void Execute() const final;
    ~WidgetTask();
};

#define WIDGETTASK_H
#endif
