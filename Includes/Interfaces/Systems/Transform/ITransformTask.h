#if !defined(ITRANSFORMTASK_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class ITransformTask : public ITask
{
private:
protected:
public:

    ESystemType GetType() final { return ESystemType::TRANSFORM; }
    virtual void Execute() const = 0;
    virtual ~ITransformTask() {}
};

#define ITRANSFORMTASK_H
#endif
