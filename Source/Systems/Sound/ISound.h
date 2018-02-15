#if !defined(ISOUND_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
class ISound : public ISystem
{
private:
protected:
public:

    virtual ISoundScene* CreateScene() = 0;
    ESystemType GetType() final { return ESystemType::SOUND; }
    virtual ~ISound() {}
};

#define ISOUND_H
#endif
