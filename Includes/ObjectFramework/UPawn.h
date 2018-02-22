#if !defined(UPAWN_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

class OBJECTFRAMEWORK_API UPawn : public UActor
{
private:
    UController* m_Controller;
protected:
    inline UController* GetController() { return m_Controller; }    

        
    inline virtual void SetIsSceneDead(bool IsSceneDead) override
    {
        m_IsSceneDead = IsSceneDead;
        if(m_Controller)
            m_Controller->SetIsSceneDead(IsSceneDead);
    }
    
    
public:
    UPawn(FObjectConstructor* ObjectConstructor);
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    void ChangeController(UController* Controller);
    
    virtual ~UPawn();
};

#define UPAWN_H
#endif
