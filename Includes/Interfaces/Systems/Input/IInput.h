#if !defined(IINPUT_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
class IInput : public ISystem
{
private:
protected:
public:

    virtual IInputScene* CreateScene() = 0;
    virtual void DestroyScene(IInputScene** Scene) = 0;
    ESystemType GetType() final { return ESystemType::INPUT; }
    virtual ~IInput() {}
};


//NOTE(EVERYONE): If we need managers add them here
typedef IInput* fp_CreateInputSystem(class FLogger* Logger, class IMemoryManager* MemoryManager);
typedef void fp_DestroyInputSystem(IInput** System);

#define IINPUT_H
#endif
