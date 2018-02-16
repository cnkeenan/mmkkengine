#if !defined(INPUTTASK_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class InputTask : public IInputTask
{
private:
protected:
public:

    InputTask();
    void Execute() const final;
    ~InputTask();
};

#define INPUTTASK_H
#endif
