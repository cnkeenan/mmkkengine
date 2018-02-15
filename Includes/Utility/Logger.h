#if !defined(LOGGER_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

#if DEBUG_BUILD
#define LOG_ASSERT(x)                           \
    do                                          \
    {                                           \
        if(!(x))                                \
            INVALID_CODE_PATH;                  \
    } while(0)
#else
#define LOG_ASSERT(x)
#endif

#if POSIX
#define MKDIR(x, y) mkdir(x, y)
#elif OS_WINDOWS
#include <direct.h>
#define MKDIR(x, y) _mkdir(x)
#endif


enum class ELogLevel
{
    FAILURE,
    WARNING,    
    DEBUG,
    INFO,
};
 
enum class EConsoleColor
{
    RED,
    GREEN,
    BLUE,
    BLACK,
    WHITE
};

enum class ELoggerType
{
    CONSOLE,
    FILE,
    BOTH
};

#define NUMBER_OF_CHANNELS 3
enum class ELogChannel
{    
    RESERVED_CHANNEL, //NOTE(EVERYONE): This channel should always be on. For things like ASSERT
    ENGINE_CHANNEL,
    PLATFORM_CHANNEL,    
};

typedef char* FNowTime(char* Result);
typedef void FChangeConsoleColor(EConsoleColor BackgroundColor, EConsoleColor ForegroundColor);

#define TurnChannelOn(x) TurnChannelOn_(ELogChannel::x)
#define TurnChannelOff(x) TurnChannelOff_(ELogChannel::x)

class FLog
{
private:
    //NOTE(EVERYONE): Statics    
    static const char* RESERVED_CHANNEL_PATH;
    static const char* ENGINE_CHANNEL_PATH;
    static const char* PLATFORM_CHANNEL_PATH;
    static const char* DUMP_PATH;
        
    struct FLogFile
    {
        FILE* File;
        const char* Path;
    };
    
    static FNowTime* s_NowTime;
    static FChangeConsoleColor* s_ChangeConsoleColor;
    static int s_Verbosity;
    static uint64 s_Channels;    
    static FLogFile s_ChannelFiles[NUMBER_OF_CHANNELS];
    static FILE* s_LogDump;
    static IMutex* s_Mutex;
    
private:
    char m_Logger[1024];
    ELogLevel m_Level;
    ELogChannel m_Channel;
    ELoggerType m_LogType;

    
public:
    inline FLog(ELogLevel Level, ELogChannel Channel, ELoggerType LogType) : m_Level(Level),
                                                                             m_Channel(Channel),
                                                                             m_LogType(LogType)
    {}
    
    inline ~FLog()
    {
        uint64 IntChannel = (uint64)m_Channel;
        if((s_Verbosity >= (int)m_Level) && CHECK_BIT_64(s_Channels, IntChannel))
        {
            EConsoleColor BackgroundColor;
            EConsoleColor ForegroundColor;
        
            switch(m_Level)
            {
                case ELogLevel::FAILURE:
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

            s_ChangeConsoleColor(BackgroundColor, ForegroundColor);
            char OutputBuffer[2048];
            char TimeBuffer[128];
            sprintf(OutputBuffer, "- CHANNEL: %s\t TIME: %s\t %s:\t %s\n", ToString(m_Channel), s_NowTime(TimeBuffer),
                    ToString(m_Level), m_Logger);            

            s_Mutex->Lock();
            //NOTE(EVERYONE): Print to console stderr
            if((m_LogType == ELoggerType::CONSOLE) || (m_LogType == ELoggerType::BOTH))
            {
                fprintf(stderr, OutputBuffer);
                fflush(stderr);
            }

            //NOTE(EVERYONE): Print to dump file

            if((m_LogType == ELoggerType::FILE) || (m_LogType == ELoggerType::BOTH))
            {
                fprintf(s_LogDump, OutputBuffer);
                fflush(s_LogDump);

                //NOTE(EVERYONE): Print to channel file
                FILE* FileHandle = s_ChannelFiles[(int)m_Channel].File;
                fprintf(FileHandle, OutputBuffer);
                fflush(FileHandle);
                long int StreamPosition = ftell(FileHandle);
                if(StreamPosition > MEGABYTE(10))
                {
                    LOG_ASSERT(!"If the log file is this large it may be too cluttered. Generic counters (like fps) should be outputted via text rendering"); 
                    freopen(s_ChannelFiles[(int)m_Channel].Path, "w", FileHandle);
                }
            }

            s_Mutex->Unlock();
        }
    }

    
    inline void Format(const char* Format, ...)
    {
        va_list Arguments;
        va_start(Arguments, Format);
        vsprintf(m_Logger, Format, Arguments);    
        va_end(Arguments);
    }

    static inline bool DirectoryExists(const char* AbsDirectoryPath)
    {
        struct stat status;

#if POSIX
#define ACCESS(x, y) access(x, y)
#elif OS_WINDOWS
#define ACCESS(x, y) _access(x, y)
#endif

        if (ACCESS(AbsDirectoryPath, 0) == 0)
        {
            stat(AbsDirectoryPath, &status);

            return (status.st_mode & S_IFDIR) != 0;
        }
        return false;
    }

    static inline void CreateDirectories()
    {
        const char* logdirs[] = { 
            "../Data",
            "../Data/Log",
            "../Data/Log/Engine_Log",
            "../Data/Log/Platform_Log",
            "../Data/Log/Reserved_Log"
        }; 

        size_t ndirs = sizeof(logdirs)/sizeof(logdirs[0]); 

        for (size_t i = 0; i < ndirs; i++)
        {
            if (!FLog::DirectoryExists(logdirs[i]))
            {
                MKDIR(logdirs[i], 0733);
            }
        }

    }

    static inline void InitLogger(FNowTime* NowTime, FChangeConsoleColor* ChangeConsoleColor,
                                  IMutex* Mutex)
    {
        s_NowTime = NowTime;
        s_ChangeConsoleColor = ChangeConsoleColor;
        s_Mutex = Mutex;
        
#define CHANNEL_CREATE(x) s_ChannelFiles[(uint64)ELogChannel::x].Path = x##_PATH; \
        s_ChannelFiles[(uint64)ELogChannel::x].File = fopen(x##_PATH, "w")
        FLog::CreateDirectories();

        s_LogDump = fopen(DUMP_PATH, "w");        
        CHANNEL_CREATE(RESERVED_CHANNEL);
        CHANNEL_CREATE(ENGINE_CHANNEL);
        CHANNEL_CREATE(PLATFORM_CHANNEL);        
    }

    static inline void DestroyLogger(FDelegate<void, IMutex*> DestroyMutex)
    {        
        fclose(s_ChannelFiles[(uint64)ELogChannel::RESERVED_CHANNEL].File);
        fclose(s_ChannelFiles[(uint64)ELogChannel::ENGINE_CHANNEL].File);
        fclose(s_ChannelFiles[(uint64)ELogChannel::PLATFORM_CHANNEL].File);
        fclose(s_LogDump);
        DestroyMutex(s_Mutex);
    }

    static inline void SetVerbosity(int Verbosity)
    {
        s_Verbosity = Verbosity;
    }

    static inline void TurnChannelOn_(ELogChannel Channel)
    {
        LOG_ASSERT(Channel != ELogChannel::RESERVED_CHANNEL);
        uint64 IntChannel = (uint64)Channel;
        SET_BIT_64(s_Channels, IntChannel);
    }

    static inline void TurnChannelOff_(ELogChannel Channel)
    {
        LOG_ASSERT(Channel != ELogChannel::RESERVED_CHANNEL);
        unsigned long IntChannel = (unsigned long)Channel;
        CLEAR_BIT_64(s_Channels, IntChannel);
    }

    static inline const char* ToString(ELogLevel Level) 
    {
        switch(Level)
        {
            case ELogLevel::FAILURE:
            {
                return "FAILURE";
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
                LOG_ASSERT(false);
                return "ERROR";
            } break;
        }
    }

    static inline const char* ToString(ELogChannel Channel)
    {
        switch(Channel)
        {
            case ELogChannel::RESERVED_CHANNEL:
            {
                return "RESERVED";
            } break;

            case ELogChannel::ENGINE_CHANNEL:
            {
                return "ENGINE";
            } break;

            case ELogChannel::PLATFORM_CHANNEL:
            {
                return "PLATFORM";
            } break;

            default:
            {
                LOG_ASSERT(false);
                return "ERROR";
            } break;
        }
    }
public:    
};

#if !OS_MAC
#ifndef STATIC_LOG_IMPLEMENTATION
FNowTime* FLog::s_NowTime = nullptr;
FChangeConsoleColor* FLog::s_ChangeConsoleColor = nullptr;
int FLog::s_Verbosity = (int)ELogLevel::INFO;
uint64 FLog::s_Channels = 0xFFFFFFFFFFFFFFFF;
FLog::FLogFile FLog::s_ChannelFiles[NUMBER_OF_CHANNELS] = {};
FILE* FLog::s_LogDump = nullptr;
const char* FLog::RESERVED_CHANNEL_PATH =  "../Data/Log/Reserved_Log/Reserved.log";
const char* FLog::ENGINE_CHANNEL_PATH = "../Data/Log/Engine_Log/Engine.log";
const char* FLog::PLATFORM_CHANNEL_PATH = "../Data/Log/Platform_Log/Platform.log";
const char* FLog::DUMP_PATH = "../Data/Log/Dump.log";
IMutex* FLog::s_Mutex = nullptr;
#define STATIC_LOG_IMPLEMENTATION
#endif
#endif

//NOTE(EVERYONE): I (JJ) timed the logger. It takes about 0.1-0.3ms to execute. It does not matter
//if it's a file log, console log, or both. Remember we have a 16.67ms limit per frame, so don't log to often.
//Not entirely sure where we can optimize. Its about 3 times slower than printf

#define LOG(level, channel, format, ...) FLog(ELogLevel::level, ELogChannel::channel, ELoggerType::BOTH).Format(format, ##__VA_ARGS__) 
#define FILE_LOG(level, channel, format, ...) FLog(ELogLevel::level, ELogChannel::channel, ELoggerType::FILE).Format(format, ##__VA_ARGS__)
#define CONSOLE_LOG(level, channel, format, ...) FLog(ELogLevel::level, ELogChannel::channel, ELoggerType::CONSOLE).Format(format, ##__VA_ARGS__)

#define LOGGER_H
#endif
