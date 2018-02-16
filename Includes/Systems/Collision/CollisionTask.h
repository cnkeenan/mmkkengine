#if !defined(COLLISIONTASK_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class CollisionTask : public ICollisionTask
{
private:
protected:
public:

    CollisionTask();
    void Execute() const final;
    ~CollisionTask();
};

#define COLLISIONTASK_H
#endif
