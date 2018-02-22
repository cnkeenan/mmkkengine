/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

GraphicsTask::GraphicsTask()
{
}

void GraphicsTask::Execute() const
{
    gPlatformManager->MakeContextCurrent(gWindow);
    FOpenGL* OpenGL = gPlatformManager->GetOpenGL();
                    
    OpenGL->glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    OpenGL->glClear(GL_COLOR_BUFFER_BIT);        
    
    OpenGL->glBegin(GL_TRIANGLES);
    OpenGL->glVertex2f(-0.5f, -0.5f);
    OpenGL->glVertex2f(0.0f, 0.5f);
    OpenGL->glVertex2f(0.5f, -0.5f);
    OpenGL->glEnd();

    gWindow->SwapOpenGLBuffers();
    
    gPlatformManager->MakeContextCurrent(nullptr);

    
}

GraphicsTask::~GraphicsTask()
{
}
