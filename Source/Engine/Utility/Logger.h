#if !defined(LOGGER_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include "Libs.h"
#include <stdarg.h>

enum class ELogLevel
{
    ERROR,
    WARNING,    
    DEBUG,
    INFO,
};

typedef char* FNowTime(char* Result);
typedef void FChangeConsoleColor(EConsoleColor BackgroundColor, EConsoleColor ForegroundColor);

class FLog
{
private:
    char Logger[1024];
    ELogLevel Level;

    static FNowTime* NowTime;
    static FChangeConsoleColor* ChangeConsoleColor;
    static int Verbosity;
    
public:
    inline FLog(ELogLevel Level = ELogLevel::INFO);
    inline ~FLog();

    
    inline void Format(const char* Format, ...);

    static inline void InitLogger(FNowTime* NowTime, FChangeConsoleColor* ChangeConsoleColor)
    {
        FLog::NowTime = NowTime;
        FLog::ChangeConsoleColor = ChangeConsoleColor;
    }

    static inline void SetVerbosity(int Verbosity)
    {
        FLog::Verbosity = Verbosity;
    }

    static inline const char* ToString(ELogLevel Level) 
    {
        switch(Level)
        {
            case ELogLevel::ERROR:
            {
                return "ERROR";
            } break;

            case ELogLevel::WARNING:
            {
                return "WARNING";
            } break;

            case ELogLevel::INFO:
            {
                return "INFO";
            } break;

            case ELogLevel::DEBUG:
            {
                return "DEBUG";
            } break;

            default:
            {
                return "FAILURE";
            } break;
        }
    }
public:    
};

FNowTime* FLog::NowTime = nullptr;
FChangeConsoleColor* FLog::ChangeConsoleColor = nullptr;
int FLog::Verbosity = (int)ELogLevel::INFO;

inline FLog::FLog(ELogLevel Level)
{
    this->Level = Level;
}

inline void FLog::Format(const char* Format,
                          ...)
{    
    va_list Arguments;
    va_start(Arguments, Format);
    vsprintf(Logger, Format, Arguments);    
    va_end(Arguments);
}

inline FLog::~FLog()
{
    if(Verbosity >= (int)Level)
    {
        EConsoleColor BackgroundColor;
        EConsoleColor ForegroundColor;
        
        switch(Level)
        {
            case ELogLevel::ERROR:
            {                
                BackgroundColor = EConsoleColor::RED;
                ForegroundColor = EConsoleColor::WHITE;
            } break;

            case ELogLevel::WARNING:
            {                
                BackgroundColor = EConsoleColor::BLACK;
                ForegroundColor = EConsoleColor::RED;
            } break;

            case ELogLevel::DEBUG:
            {
                BackgroundColor = EConsoleColor::BLACK;
                ForegroundColor = EConsoleColor::GREEN;
            } break;

            case ELogLevel::INFO:
            {
                BackgroundColor = EConsoleColor::BLACK;
                ForegroundColor = EConsoleColor::WHITE;
            } break;
        }
        ChangeConsoleColor(BackgroundColor, ForegroundColor);
        char Buffer[128];
        fprintf(stderr, "- %s %s: \t%s\n", NowTime(Buffer), ToString(Level), Logger);
        fflush(stderr);
    }
}

#define LOG(level, format, ...) \
    //FLog(ELogLevel:: ## level).Format(format, __VA_ARGS__)



#define LOGGER_H
#endif
