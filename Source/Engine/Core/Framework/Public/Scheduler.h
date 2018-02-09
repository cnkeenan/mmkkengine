class FScheduler
{
private:
    FHighResolutionTimer m_MasterClock;    
    uint64 m_StartTimer;
    double m_Frequency;
    double m_Lag;
public:
    void Init(double Frequency);
    double Tick();
    inline void SetFrequency(double Frequency) { m_Frequency = Frequency; };
};
