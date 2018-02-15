#if !defined(USCENE_H)

class OBJECTFRAMEWORK_API UScene
{
private:
public:
    UScene();
    virtual void BeginPlay();
    virtual void Tick(float DeltaTime);
    virtual ~UScene();
};

#define USCENE_H
#endif
