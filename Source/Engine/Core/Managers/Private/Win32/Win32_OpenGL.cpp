/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

void* Win32_GetGLFunction(const char *name)
{
    void *p = (void *)wglGetProcAddress(name);
    if(p == 0 ||
       (p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) ||
       (p == (void*)-1) )
    {
        HMODULE module = LoadLibraryA("opengl32.dll");
        p = (void *)GetProcAddress(module, name);
    }

    return p;
}

void PlatformManager::InitializeOpenGLContext(IWindow* Window)
{
    Win32_Window* ActualWindow = (Win32_Window*)Window;
    ActualWindow->m_DeviceContext = GetDC(ActualWindow->m_Window);

    PIXELFORMATDESCRIPTOR PixelFormatDescriptor[2] = {};
    PixelFormatDescriptor[0].nSize = sizeof(PIXELFORMATDESCRIPTOR);
    PixelFormatDescriptor[0].nVersion = 1;
    PixelFormatDescriptor[0].dwFlags = PFD_SUPPORT_OPENGL|PFD_DRAW_TO_WINDOW|PFD_DOUBLEBUFFER;
    PixelFormatDescriptor[0].cColorBits = 32;
    PixelFormatDescriptor[0].cAlphaBits = 8;
    PixelFormatDescriptor[0].iLayerType = PFD_MAIN_PLANE;

    int32 SuggestedPixelFormatIndex = ChoosePixelFormat(ActualWindow->m_DeviceContext, PixelFormatDescriptor);
    DescribePixelFormat(ActualWindow->m_DeviceContext, SuggestedPixelFormatIndex, sizeof(PIXELFORMATDESCRIPTOR),
                        &PixelFormatDescriptor[1]);
    SetPixelFormat(ActualWindow->m_DeviceContext, SuggestedPixelFormatIndex, &PixelFormatDescriptor[1]);

    ActualWindow->m_RenderingContext = wglCreateContext(ActualWindow->m_DeviceContext);
    if(wglMakeCurrent(ActualWindow->m_DeviceContext, ActualWindow->m_RenderingContext))
    {
#define LOAD_GL_FUNCTION(x) x = (fp_##x*)Win32_GetGLFunction(#x)
        //TODO(JJ): Modern opengl initialization
        LOAD_GL_FUNCTION(glClear);
        LOAD_GL_FUNCTION(glClearColor);
    }
}
