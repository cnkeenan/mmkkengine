#if !defined(IAITASK_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class IAITask : public ITask
{
private:
protected:
public:

    ESystemType GetType() final { return ESystemType::AI; }
    virtual void Execute() const = 0;
    virtual ~IAITask() {}
};

#define IAITASK_H
#endif
