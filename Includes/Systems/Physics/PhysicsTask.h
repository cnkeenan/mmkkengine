#if !defined(PHYSICSTASK_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class PhysicsTask : public IPhysicsTask
{
private:
protected:
public:

    PhysicsTask();
    void Execute() const final;
    ~PhysicsTask();
};

#define PHYSICSTASK_H
#endif
