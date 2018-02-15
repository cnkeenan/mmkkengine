#if !defined(ITASK_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class ITask
{
private:
protected:
public:

    virtual ESystemType GetType() = 0;
    virtual void Execute() const = 0;
    virtual ~ITask() {}
};

#define ITASK_H
#endif
