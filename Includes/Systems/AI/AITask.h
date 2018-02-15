#if !defined(AITASK_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class AITask : public IAITask
{
private:
protected:
public:
    AITask();
    void Execute() const final;
    ~AITask();
};

#define AITASK_H
#endif
