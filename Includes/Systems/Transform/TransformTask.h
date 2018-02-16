#if !defined(TRANSFORMTASK_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class TransformTask : public ITransformTask
{
private:
protected:
public:

    TransformTask();
    void Execute() const final;
    ~TransformTask();
};

#define TRANSFORMTASK_H
#endif
