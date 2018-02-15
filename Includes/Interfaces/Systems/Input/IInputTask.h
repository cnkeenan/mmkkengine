#if !defined(IINPUTTASK_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class IInputTask : public ITask
{
private:
protected:
public:

    ESystemType GetType() final { return ESystemType::INPUT; }
    virtual void Execute() const = 0;
    virtual ~IInputTask() {}
};

#define IINPUTTASK_H
#endif
