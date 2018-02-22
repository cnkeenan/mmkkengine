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

enum class ELogType
{
    CONSOLE,
    FILE,
    BOTH
};

#define NUMBER_OF_CHANNELS 11
enum class ELogChannel
{    
    RESERVED_CHANNEL, //NOTE(EVERYONE): This channel should always be on. For things like ASSERT
    ENGINE_CHANNEL,
    PLATFORM_CHANNEL,
    AI_CHANNEL,
    COLLISION_CHANNEL,
    GRAPHICS_CHANNEL,
    INPUT_CHANNEL,
    PHYSICS_CHANNEL,
    SOUND_CHANNEL,
    TRANSFORM_CHANNEL,
    WIDGET_CHANNEL
};

inline char* GetCurrentTime(char* Result);
inline void ChangeConsoleColor(EConsoleColor BackgroundColor, EConsoleColor ForegroundColor);

#define TurnChannelOn(x) TurnChannelOn_(ELogChannel::x)
#define TurnChannelOff(x) TurnChannelOff_(ELogChannel::x)

struct FLogFile
{
    FILE* File;
    const char* Path;
};

#define RESERVED_CHANNEL_PATH "../Data/Log/Reserved_Log/Reserved.log"
#define ENGINE_CHANNEL_PATH "../Data/Log/Engine_Log/Engine.log"            
#define PLATFORM_CHANNEL_PATH "../Data/Log/Platform_Log/Platform.log"
#define AI_CHANNEL_PATH "../Data/Log/AI_Log/AI.log"
#define COLLISION_CHANNEL_PATH "../Data/Log/Collision_Log/Collision.log"
#define GRAPHICS_CHANNEL_PATH "../Data/Log/Graphics_Log/Graphics.log"
#define INPUT_CHANNEL_PATH "../Data/Log/Input_Log/Input.log"
#define PHYSICS_CHANNEL_PATH "../Data/Log/Physics_Log/Physics.log"
#define SOUND_CHANNEL_PATH "../Data/Log/Sound_Log/Sound.log"
#define TRANSFORM_CHANNEL_PATH "../Data/Log/Transform_Log/Transform.log"
#define WIDGET_CHANNEL_PATH "../Data/Log/Widget_Log/Widget.log"

class FLogger
{
        
    int m_Verbosity;
    uint64 m_Channels;        

public:

    inline FLogger()
    {
        m_Verbosity = (int)ELogLevel::INFO;
        m_Channels = 0xFFFFFFFFFFFFFFFF;        

        CreateDirectories();                
    }    

    inline void SetVerbosity(int Verbosity)
    {
        m_Verbosity = Verbosity;
    }

    inline void TurnChannelOn_(ELogChannel Channel)
    {
        if(Channel == ELogChannel::RESERVED_CHANNEL)
            INVALID_CODE_PATH;

        uint64 IntChannel = (uint64)Channel;
        SET_BIT_64(m_Channels, IntChannel);
    }

    inline void TurnChannelOff_(ELogChannel Channel)
    {
        if(Channel == ELogChannel::RESERVED_CHANNEL)
            INVALID_CODE_PATH;

        uint64 IntChannel = (uint64)Channel;
        CLEAR_BIT_64(m_Channels, IntChannel);
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
                INVALID_CODE_PATH;
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

            case ELogChannel::AI_CHANNEL:
            {
                return "AI";
            } break;
            
            case ELogChannel::COLLISION_CHANNEL:
            {
                return "COLLISION";
            } break;
            
            case ELogChannel::GRAPHICS_CHANNEL:
            {
                return "GRAPHICS";
            } break;
            
            case ELogChannel::INPUT_CHANNEL:
            {
                return "INPUT";
            } break;
            
            case ELogChannel::PHYSICS_CHANNEL:
            {
                return "PHYSICS";
            } break;
            
            case ELogChannel::SOUND_CHANNEL:
            {
                return "SOUND";
            } break;
            
            case ELogChannel::TRANSFORM_CHANNEL:
            {
                return "TRANSFORM";
            } break;
            
            case ELogChannel::WIDGET_CHANNEL:
            {
                return "WIDGET";
            } break;

            default:
            {
                INVALID_CODE_PATH;
                return "ERROR";
            } break;
        }
    }
    
    inline bool DirectoryExists(const char* AbsDirectoryPath)
    {
        struct stat status;


        if (ACCESS(AbsDirectoryPath, 0) == 0)
        {
            stat(AbsDirectoryPath, &status);

            return (status.st_mode & S_IFDIR) != 0;
        }
        return false;
    }
    
    inline void CreateDirectories()
    {
        const char* logdirs[] = { 
            "../Data",
            "../Data/Log",
            "../Data/Log/Engine_Log",
            "../Data/Log/Platform_Log",
            "../Data/Log/Reserved_Log",
            "../Data/Log/AI_Log",
            "../Data/Log/Collision_Log",
            "../Data/Log/Graphics_Log",
            "../Data/Log/Input_Log",
            "../Data/Log/Physics_Log",
            "../Data/Log/Sound_Log",
            "../Data/Log/Transform_Log",
            "../Data/Log/Widget_Log"
        };

        size_t ndirs = sizeof(logdirs)/sizeof(logdirs[0]); 

        for (size_t i = 0; i < ndirs; i++)
        {
            if (!FLogger::DirectoryExists(logdirs[i]))
            {
                MKDIR(logdirs[i], 0733);
            }
        }

    }
    
    inline void Log(ELogLevel Level, ELogChannel Channel, ELogType LogType, FILE* FileHandle,
                    const char* FilePath, const char* Format, ...)
    {        
        char Buffer[512];
        va_list Arguments;
        va_start(Arguments, Format);
        vsprintf(Buffer, Format, Arguments);
        va_end(Arguments);

        EConsoleColor BackgroundColor = EConsoleColor::BLACK;
        EConsoleColor ForegroundColor = EConsoleColor::WHITE;

        switch(Level)
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
        }

        ChangeConsoleColor(BackgroundColor, ForegroundColor);
        char ResultBuffer[1024];
        char TimeBuffer[128];
        sprintf(ResultBuffer, "- CHANNEL: %s\t TIME: %s\t %s:\t %s\n",
                ToString(Channel), GetCurrentTime(TimeBuffer),
                ToString(Level), Buffer);

        switch(LogType)
        {
            case ELogType::BOTH:
            {                
                fprintf(stderr, ResultBuffer);                                    
                fprintf(FileHandle, ResultBuffer);

                _flushall();                

                long int StreamPosition = ftell(FileHandle);
                if(StreamPosition > GIGABYTE(1))
                {                        
                    freopen(FilePath, "w", FileHandle);
                }

            } break;

            case ELogType::CONSOLE:
            {
                fprintf(stderr, ResultBuffer);
                fflush(stderr);
            } break;

            case ELogType::FILE:
            {                
                fprintf(FileHandle, ResultBuffer);
                fflush(FileHandle);                

                long int StreamPosition = ftell(FileHandle);
                if(StreamPosition > GIGABYTE(1))
                {                        
                    freopen(FilePath, "w", FileHandle);
                }
            } break;
        }
        
    }

    ~FLogger()
    {                
    }
    
};

extern FLogger* gLogger;

#define LOG(level, channel, format, ...) gLogger->Log(ELogLevel::level, ELogChannel::channel, ELogType::BOTH, channel##_File, channel##_PATH, format, ##__VA_ARGS__)
#define FILE_LOG(level, channel, format, ...) gLogger->Log(ELogLevel::level, ELogChannel::channel, ELogType::FILE, channel##_File, channel##_PATH, format, ##__VA_ARGS__)
#define CONSOLE_LOG(level, channel, format, ...) gLogger->Log(ELogLevel::level, ELogChannel::channel, ELogType::CONSOLE, channel##_File, channel##_PATH, format, ##__VA_ARGS__)

#if OS_WINDOWS
#include <Windows.h>
#undef GetCurrentTime
char* GetCurrentTime(char* Result)
{
    static LARGE_INTEGER Frequency;
    if(Frequency.QuadPart == 0)
        QueryPerformanceFrequency(&Frequency);

    char Buffer[64];
    GetTimeFormat(LOCALE_USER_DEFAULT, 0, 0, "HH':'mm':'ss", Buffer, sizeof(Buffer));

    static LARGE_INTEGER StartTime;
    if(StartTime.QuadPart == 0)
        QueryPerformanceCounter(&StartTime);

    LARGE_INTEGER EndTime;
    QueryPerformanceCounter(&EndTime);

    uint64 Elapsed = (EndTime.QuadPart-StartTime.QuadPart)*1000;
    Elapsed /= Frequency.QuadPart;

    sprintf(Result, "%s.%03I64d", Buffer, Elapsed%1000);
    return Result;
}

void ChangeConsoleColor(EConsoleColor BackgroundColor, EConsoleColor ForegroundColor)
{
    HANDLE Console = GetStdHandle(STD_ERROR_HANDLE);

    WORD Attributes = 0;

    switch(ForegroundColor)
    {
        case EConsoleColor::RED:
        {
            Attributes = FOREGROUND_RED;
        } break;

        case EConsoleColor::GREEN:
        {
            Attributes = FOREGROUND_GREEN;
        } break;

        case EConsoleColor::BLUE:
        {
            Attributes = FOREGROUND_BLUE;
        } break;

        case EConsoleColor::WHITE:
        {
            Attributes = FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED;
        } break;
    }
    
    switch(BackgroundColor)
    {
        case EConsoleColor::RED:
        {
            Attributes |= BACKGROUND_RED;
        } break;

        case EConsoleColor::GREEN:
        {
            Attributes |= BACKGROUND_GREEN;
        } break;

        case EConsoleColor::BLUE:
        {
            Attributes |= BACKGROUND_BLUE;
        } break;

        case EConsoleColor::WHITE:
        {
            Attributes |= BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED;
        } break;
    }
    SetConsoleTextAttribute(Console, Attributes);
}

#elif POSIX
char* GetCurrentTime(char* Result)
{    
    static timespec Start;
    if(First.tv_sec == 0)
        clock_gettime(CLOCK_TYPE, &First);

    timespec End;
    clock_gettime(CLOCK_TYPE, &End);
    
    double Elapsed = ((End.tv_sec-Start.tv_sec)*1000) + ((End.tv_nsec - Start.tv_nsec)/1000000.0);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    sprintf(Result, "%d:%d:%d.%d", tm.tm_hour, tm.tm_min, tm.tm_sec, (int)Elapsed % 1000);
    return Result; 
}


void ChangeConsoleColor(EConsoleColor BackgroundColor, EConsoleColor ForegroundColor)
{
    switch(ForegroundColor)
    {
        case EConsoleColor::RED:
        {
            system("tput setaf 1");
        } break;

        case EConsoleColor::GREEN:
        {
            system("tput setaf 2");
        } break;

        case EConsoleColor::BLUE:
        {
            system("tput setaf 4");
        } break;

        case EConsoleColor::WHITE:
        {
            system("tput setaf 7");
        } break;

        case EConsoleColor::BLACK:
        {
            system("tput setaf 0");
        } break;

    }
    
    switch(BackgroundColor)
    {
        case EConsoleColor::RED:
        {
            system("tput setab 1");
        } break;

        case EConsoleColor::GREEN:
        {
            system("tput setab 2");
        } break;

        case EConsoleColor::BLUE:
        {
            system("tput setab 4");
        } break;

        case EConsoleColor::WHITE:
        {
            system("tput setab 7");
        } break;
        case EConsoleColor::BLACK:
        {
            system("tput setab 0");
        } break;
    }
}

#endif

#define LOGGER_H
#endif
