#if !defined(IPHYSICSTASK_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class IPhysicsTask : public ITask
{
private:
protected:
public:

    
    ESystemType GetType() final { return ESystemType::PHYSICS; }
    virtual void Execute() const = 0;
    virtual ~IPhysicsTask() {}
};

#define IPHYSICSTASK_H
#endif
