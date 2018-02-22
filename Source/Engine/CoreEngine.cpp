/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

#include <Engine/CoreEngine.h>

#if OS_MAC
#include <OpenGL/gl.h>
#endif

FLogger* gLogger = nullptr;

void FCoreEngine::Initialize()
{
    m_FPS = 60;
    ENGINE_CHANNEL_File = fopen(ENGINE_CHANNEL_PATH, "w");
    PLATFORM_CHANNEL_File = fopen(PLATFORM_CHANNEL_PATH, "w");
    static FLogger StaticLogger;
    gLogger = &StaticLogger;
    InitializeFramework(MemoryManager::Get());
    PlatformManager* Platform = PlatformManager::Get();    
    m_MainWindow = Platform->CreateWindow(1280, 720, "Marty-O");
    m_Loader.Initialize(m_MainWindow);
}

void FCoreEngine::Tick()
{    
    m_Scheduler.Init(1.0/(double)m_FPS);

    EnvironmentManager* Environment = EnvironmentManager::Get();

    UWorld* World = m_Loader.Load();

    FHighResolutionTimer Timer = PlatformManager::Get()->CreateHighResolutionTimer();
    
    World->BeginPlay();
    FOpenGL* OpenGL = PlatformManager::Get()->GetOpenGL();
    while(Environment->ExecutionState() != EExecutionState::EXIT)
    {                
        
        m_MainWindow->ProcessOSWindowMessages();

        double DeltaTime = m_Scheduler.Tick(World);
        //NOTE(EVERYONE): This is the beginning of the new frame
        
        //NOTE(EVERYONE): We'll let the main thread start working on tasks while it waits for the
        //frame's current tasks to finish execution
        TaskManager::Get()->CompleteAllSubmittedTasks();        
        
        //NOTE(EVERYONE): State manager distribution here
                
        World->Tick((float)DeltaTime);        
        
        if(Environment->ExecutionState() == EExecutionState::NEW_SCENE)
        {
            m_Loader.Unload(World);
            World = m_Loader.Load();
            World->BeginPlay();
        }

    }
    m_Loader.Unload(World);
}

void FCoreEngine::Destroy()
{
    m_Loader.Destroy();
    PlatformManager::Get()->DestroyWindow(m_MainWindow);
    m_MainWindow = nullptr;
    fclose(ENGINE_CHANNEL_File);
    fclose(PLATFORM_CHANNEL_File);
}

int main(int ArgumentCount, char** Arguments)
{
    MemoryManager::Get();
    PlatformManager::Get();    
    TaskManager::Get();
    EnvironmentManager::Get();
    StateManager::GetSceneStateManager();
    StateManager::GetObjectStateManager();
    ServiceManager::Get();    
    FCoreEngine Engine;    
    Engine.Initialize();
    Engine.Tick();
    Engine.Destroy();
    delete ServiceManager::Get();
    delete StateManager::GetObjectStateManager();
    delete StateManager::GetSceneStateManager();    
    delete EnvironmentManager::Get();
    delete TaskManager::Get();   
    delete PlatformManager::Get();
    return 0;
}

#include "Managers/MemoryManager.cpp"
#include "Managers/EnvironmentManager.cpp"
#include "Managers/PlatformManager.cpp"
#include "Managers/TaskManager.cpp"
#include "Managers/StateManager.cpp"
#include "Managers/ServiceManager.cpp"
#include "Framework/Scheduler.cpp"
#include "Framework/Loader.cpp"
