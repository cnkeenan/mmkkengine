#if !defined(IAI_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
class IAI : public ISystem
{
private:
protected:
public:

    virtual IAIScene* CreateScene() = 0;
    virtual void DestroyScene(IAIScene** Scene) = 0;
    ESystemType GetType() final { return ESystemType::AI; }
    virtual ~IAI() {}
};


//NOTE(EVERYONE): If we need managers add them here
typedef IAI* fp_CreateAISystem(class FLogger* Logger, class IMemoryManager* MemoryManager);
typedef void fp_DestroyAISystem(IAI** System);

#define IAI_H
#endif
