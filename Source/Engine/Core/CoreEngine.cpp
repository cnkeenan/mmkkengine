/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <PlatformDetection.h>
#include "CoreEngine.h"
#ifdef OS_LINUX
#include <GL/glu.h>
#else
#include <OpenGL.h>
#endif
#include <stdio.h>

void FCoreEngine::Initialize()
{
    m_MainWindow = PlatformManager::Get()->CreateWindow(1280, 720, "Marty-O");
    PlatformManager::Get()->InitializeOpenGLContext(m_MainWindow);
}

void FCoreEngine::Tick()
{
    bool NotRunning = false;

    FHighResolutionTimer MainLoopTimer = PlatformManager::Get()->CreateHighResolutionTimer();

    uint64 StartTimer = MainLoopTimer.StartTimer();
    while(!NotRunning)
    {
        uint64 EndTimer = MainLoopTimer.EndTimer();
        double DeltaTime = MainLoopTimer.ElapsedTime(EndTimer, StartTimer);
        printf("%fms/f\n", DeltaTime*1000.0f);
        
        StartTimer = MainLoopTimer.StartTimer();
        //NOTE(EVERYONE): This is the beginning of the new frame
        NotRunning = m_MainWindow->ProcessOSWindowMessages();

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

        m_MainWindow->SwapOpenGLBuffers();
    }
}

void FCoreEngine::Destroy()
{
    PlatformManager::Get()->DestroyWindow(m_MainWindow);
    m_MainWindow = nullptr;
}

int main(int ArgumentCount, char** Arguments)
{
    FCoreEngine Engine;
    Engine.Initialize();
    Engine.Tick();
    Engine.Destroy();
    return 0;
}

#include "Managers/Private/PlatformManager.cpp"
