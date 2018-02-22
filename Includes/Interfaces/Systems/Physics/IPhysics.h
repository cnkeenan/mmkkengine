#if !defined(IPHYSICS_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
class IPhysics : public ISystem
{
private:
protected:
public:

    virtual IPhysicsScene* CreateScene() = 0;
    virtual void DestroyScene(IPhysicsScene** Scene) = 0; 
    ESystemType GetType() final { return ESystemType::PHYSICS; }
    virtual ~IPhysics() {}
};

//NOTE(EVERYONE): If we need managers add them here
typedef IPhysics* fp_CreatePhysicsSystem(class FLogger* Logger, class IMemoryManager* MemoryManager);
typedef void fp_DestroyPhysicsSystem(IPhysics** System);


#define IPHYSICS_H
#endif
