#if !defined(ICOLLISIONTASK_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class ICollisionTask : public ITask
{
private:
protected:
public:

    ESystemType GetType() final { return ESystemType::COLLISION; }
    virtual void Execute() const = 0;
    virtual ~ICollisionTask() {}
};

#define ICOLLISIONTASK_H
#endif
