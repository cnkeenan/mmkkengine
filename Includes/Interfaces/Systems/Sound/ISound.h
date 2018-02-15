#if !defined(ISOUND_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
class ISound : public ISystem
{
private:
protected:
public:

    
    ESystemType GetType() final { return ESystemType::SOUND; }
    virtual ~ISound() {}
};

#define ISOUND_H
#endif
