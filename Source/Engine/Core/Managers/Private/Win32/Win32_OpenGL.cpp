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
        HMODULE module = LoadLibrary("opengl32.dll");
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

    wglGetProcAddress = (fp_wglGetProcAddress_*)GetProcAddress(LoadLibrary("opengl32.dll"), "wglGetProcAddress");
    wglCreateContext = (fp_wglCreateContext_*)Win32_GetGLFunction("wglCreateContext");
    wglMakeCurrent = (fp_wglMakeCurrent_*)Win32_GetGLFunction("wglMakeCurrent");
    wglDeleteContext = (fp_wglDeleteContext_*)Win32_GetGLFunction("wglDeleteContext");
    
    ActualWindow->m_RenderingContext = wglCreateContext(ActualWindow->m_DeviceContext);
    if(wglMakeCurrent(ActualWindow->m_DeviceContext, ActualWindow->m_RenderingContext))
    {

        LoadOpenGL_1_0(Win32_GetGLFunction);
         
        wglCreateContextAttribsARB = (fp_wglCreateContextAttribsARB_*)Win32_GetGLFunction("wglCreateContextAttribsARB");
        if(wglCreateContextAttribsARB)
        {
            //NOTE(EVERYONE): Modern version of opengl

            //TODO(EVERYONE): Confirm the statement below is corrects
            //NOTE(EVERYONE): Version 3.3 is the target version since all 3.1/3.2 hardware can all run 3.3 
            int Attribs[] =
            {
                WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
                WGL_CONTEXT_MINOR_VERSION_ARB, 3,
                WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB
                #if DEBUG_BUILD
                |WGL_CONTEXT_DEBUG_BIT_ARB
                #endif
                ,
                WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
                0,
            };
           
            HGLRC ShareContext = 0;
            HGLRC ModernRenderingContext = wglCreateContextAttribsARB(ActualWindow->m_DeviceContext,
                                                                      ShareContext, Attribs);
            if(ModernRenderingContext)
            {
                wglMakeCurrent(ActualWindow->m_DeviceContext, ModernRenderingContext);
                wglDeleteContext(ActualWindow->m_RenderingContext);
                ActualWindow->m_RenderingContext = ModernRenderingContext;                
                LoadOpenGL_3_3(Win32_GetGLFunction);
            }            
        }
        else
        {
            //TODO(EVERYONE): Depreciated. Discuss if we should support?
        }

        FDeviceInfo DeviceInfo = {};
        
        DeviceInfo.Vendor = glGetString(GL_VENDOR);
        DeviceInfo.Renderer = glGetString(GL_RENDERER);
        DeviceInfo.Version = glGetString(GL_VERSION);
        
        const unsigned char* Extensions = glGetString(GL_EXTENSIONS);
    }
}
