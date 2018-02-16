#if !defined(ICOLLISION_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
class ICollision : public ISystem
{
private:
protected:
public:

    virtual ICollisionScene* CreateScene() = 0;
    virtual void DestroyScene(ICollisionScene** Scene) = 0;

    ESystemType GetType() final { return ESystemType::COLLISION; }
    virtual ~ICollision() {}
};

//NOTE(EVERYONE): If we need managers add them here
typedef ICollision* fp_CreateCollisionSystem(class IMemoryManager* MemoryManager);
typedef void fp_DestroyCollisionSystem(ICollision** System);

#define ICOLLISION_H
#endif
