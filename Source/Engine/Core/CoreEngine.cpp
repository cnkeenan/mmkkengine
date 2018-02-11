/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <PlatformDetection.h>
#include "CoreEngine.h"
#include <Strings.h>
#include <Logger.h>
#if OS_LINUX
#include <GL/glu.h>
#else
#include <OpenGL.h>
#endif

void FCoreEngine::Initialize()
{
    m_FPS = 60;
    PlatformManager* Platform = PlatformManager::Get();    
    FLog::InitLogger(Platform->GetCurrentTime, Platform->ChangeConsoleColor);
    m_MainWindow = Platform->CreateWindow(1280, 720, "Marty-O");
    Platform->InitializeOpenGLContext(m_MainWindow);     
}

void FCoreEngine::Tick()
{
    bool NotRunning = false;

    m_Scheduler.Init(1.0/(double)m_FPS);

    while(!NotRunning)
    {                        
        NotRunning = m_MainWindow->ProcessOSWindowMessages();

        double DeltaTime = m_Scheduler.Tick();
        //NOTE(EVERYONE): This is the beginning of the new frame
        LOG(INFO, "%fms/f", DeltaTime*1000.0f);        

        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);        

        m_MainWindow->SwapOpenGLBuffers();
    }
}

void FCoreEngine::Destroy()
{
    PlatformManager::Get()->DestroyWindow(m_MainWindow);
    m_MainWindow = nullptr;
}
#if 0
int main(int ArgumentCount, char** Arguments)
{
    FCoreEngine Engine;
    Engine.Initialize();
    Engine.Tick();
    Engine.Destroy();
    return 0;
}
#else
int main(int ArgumentCount, char** Arguments)
{
    IWindow* window = PlatformManager::Get()->CreateWindow(1280, 720, "FUUUUUUUUCK YEEEAHHH");
    while(window);
    return 0;
}
#endif

#include "Managers/Private/PlatformManager.cpp"
#include "Managers/Private/TaskManager.cpp"
#include "Managers/Private/StateManager.cpp"
#include "Framework/Private/Scheduler.cpp"
