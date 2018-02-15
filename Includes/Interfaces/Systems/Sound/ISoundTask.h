#if !defined(ISOUNDTASK_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class ISoundTask : public ITask
{
private:
protected:
public:

    ESystemType GetType() final { return ESystemType::SOUND; }
    virtual void Execute() const = 0;
    virtual ~ISoundTask() {}
};

#define ISOUNDTASK_H
#endif
