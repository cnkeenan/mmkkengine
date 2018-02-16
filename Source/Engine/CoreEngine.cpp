/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <Engine/CoreEngine.h>
#if OS_LINUX
#include <GL/glu.h>
#else
#include <Utility/OpenGL.h>
#endif
#if OS_MAC
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>
#endif

void FCoreEngine::Initialize()
{
    m_FPS = 60;
    PlatformManager *Platform = PlatformManager::Get();
    TaskManager::Get();
    FLog::InitLogger(Platform->GetCurrentTime, Platform->ChangeConsoleColor, Platform->CreateMutex());
    m_MainWindow = Platform->CreateWindow(1280, 720, "Marty-O");
    Platform->InitializeOpenGLContext(m_MainWindow);
}

void FCoreEngine::Tick()
{
    m_Scheduler.Init(1.0 / (double)m_FPS);

    EnvironmentManager *Environment = EnvironmentManager::Get();

    FHighResolutionTimer Timer = PlatformManager::Get()->CreateHighResolutionTimer();

    while (Environment->ExecutionState() == EExecutionState::RUN)
    {
        m_MainWindow->ProcessOSWindowMessages();

        double DeltaTime = m_Scheduler.Tick();
        //NOTE(EVERYONE): This is the beginning of the new frame

        //NOTE(EVERYONE): We'll let the main thread start working on tasks while it waits for the
        //frame's current tasks to finish execution
        TaskManager::Get()->CompleteAllSubmittedTasks();

        //NOTE(EVERYONE): State manager distribution here

        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        m_MainWindow->SwapOpenGLBuffers();
    }
}

void FCoreEngine::Destroy()
{
    LOG(INFO, ENGINE_CHANNEL, "Hi");
    PlatformManager::Get()->DestroyWindow(m_MainWindow);
    m_MainWindow = nullptr;
    FLog::DestroyLogger(FDelegate<void, IMutex *>::Bind<PlatformManager, &PlatformManager::DestroyMutex>(PlatformManager::Get()));
}

int main(int ArgumentCount, char **Arguments)
{
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

#include "Managers/EnvironmentManager.cpp"
#include "Managers/PlatformManager.cpp"
#include "Managers/TaskManager.cpp"
#include "Managers/StateManager.cpp"
#include "Managers/ServiceManager.cpp"
#include "Framework/Scheduler.cpp"
