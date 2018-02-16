#if !defined(SOUNDTASK_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class SoundTask : public ISoundTask
{
private:
protected:
public:

    SoundTask();
    void Execute() const final;
    ~SoundTask();
};

#define SOUNDTASK_H
#endif
