#if !defined(SCHEDULER_H)

//TODO(EVERYONE): We can make this reusable, especially for sorting so lets move this to some
//other file in the utility headers
enum class EDistributeOrder
{
    ASCENDING,
    DESCENDING
};

class FScheduler
{
private:
    FHighResolutionTimer m_MasterClock;    
    uint64 m_StartTimer;
    double m_Frequency;
    double m_Lag;
    
    EDistributeOrder m_DistributionOrder;
public:
    void Init(double Frequency);
    double Tick();
    inline void SetFrequency(double Frequency) { m_Frequency = Frequency; };
};

#define SCHEDULER_H
#endif
