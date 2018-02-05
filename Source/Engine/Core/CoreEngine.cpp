/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include <PlatformDetection.h>
#include "CoreEngine.h"
#include <OpenGL.h>

void FCoreEngine::Initialize()
{
    m_MainWindow = PlatformManager::Get()->CreateWindow(1280, 720, "Marty-O");
    PlatformManager::Get()->InitializeOpenGLContext(m_MainWindow);
}

void FCoreEngine::Tick()
{
    bool NotRunning = false;

    while(!NotRunning)
    {
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

#include "Managers/private/PlatformManager.cpp"
