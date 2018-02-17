
struct Linux_Window : public IWindow
{
    Display*     m_Display; /* access to X Server */
    Window       m_Window;
    GLXContext   m_RenderingContext;
    GLXFBConfig  tmp_GLFBConfig;

    virtual void Initialize(
                    const int Width, const int Height, const char* WindowName);
    virtual void ProcessOSWindowMessages() final;
    virtual void SwapOpenGLBuffers() final;
};

void Linux_Window::Initialize(
            const int Width, const int Height, const char* WindowName)
{
    XSetWindowAttributes swa;
    Colormap cmap;
    int i;
    int glx_major;
    int glx_minor;
    int fbcount;
    int best_fbc, worst_fbc;
    int best_num_samp, worst_num_samp;
    int visual_attrs[] =
    {
       GLX_X_RENDERABLE  , True           ,
       GLX_DRAWABLE_TYPE , GLX_WINDOW_BIT ,
       GLX_RENDER_TYPE   , GLX_RGBA_BIT   ,
       GLX_X_VISUAL_TYPE , GLX_TRUE_COLOR ,
       GLX_RED_SIZE      , 8              ,
       GLX_GREEN_SIZE    , 8              ,
       GLX_BLUE_SIZE     , 8              ,
       GLX_ALPHA_SIZE    , 8              ,
       GLX_DEPTH_SIZE    , 24             ,
       GLX_STENCIL_SIZE  , 8              ,
       GLX_DOUBLEBUFFER  , True           ,
       None
    };

    m_Display = XOpenDisplay(NULL);
    if (!m_Display)
    {
        LOG(FAILURE, PLATFORM_CHANNEL, "Failed to open X Display\n");
    }

    if (!glXQueryVersion(m_Display, &glx_major, &glx_minor) ||
            ((glx_major == 1) && (glx_minor < 3)) ||
            (glx_major < 1))
    {
        LOG(FAILURE, PLATFORM_CHANNEL, "Invalid GLX Version");
        exit(1);
    }


    GLXFBConfig* fbc = glXChooseFBConfig(
        m_Display                ,
        DefaultScreen(m_Display) ,
        visual_attrs             ,
        &fbcount
    );

    if (!fbc)
    {
        LOG(FAILURE, PLATFORM_CHANNEL, "Failed to retreive framebuffer config");
        exit(1);
    }

    for (i = 0; i < fbcount; ++i)
    {
        XVisualInfo *vi = glXGetVisualFromFBConfig(m_Display, fbc[i]);
        if (vi)
        {
            int samp_buf, samples;

            glXGetFBConfigAttrib(
                m_Display          ,
                fbc[i]             ,
                GLX_SAMPLE_BUFFERS ,
                &samp_buf
            );

            glXGetFBConfigAttrib(
                m_Display         ,
                fbc[i]            ,
                GLX_SAMPLES       ,
                &samples
            );

            if (best_fbc < 0 || samp_buf && samples > best_num_samp)
            {
                best_fbc = i;
                best_num_samp = samples;
            }

            if (worst_fbc < 0 || !samp_buf || samples < worst_num_samp)
            {
                worst_fbc = i;
                worst_num_samp = samples;
            }
        }
        XFree(vi);
    }

    tmp_GLFBConfig = fbc[best_fbc];
    XFree(fbc);

    XVisualInfo *vi = glXGetVisualFromFBConfig(m_Display, tmp_GLFBConfig);
    cmap = XCreateColormap(
            m_Display                          ,
            RootWindow(m_Display , vi->screen) ,
            vi->visual                         ,
            AllocNone
    );

    swa.colormap = cmap;
    swa.background_pixmap = None;
    swa.border_pixel = 0;
    swa.event_mask =  StructureNotifyMask | ExposureMask | KeyPressMask | KeyReleaseMask;

    m_Window = XCreateWindow(
        m_Display                               ,
        RootWindow(m_Display, vi->screen)       ,
        0                                       , // x position
        0                                       , // y position
        Width                                   ,
        Height                                  ,
        0                                       , // border width
        vi->depth                               , // depth
        InputOutput                             , // window class
        vi->visual                              ,
        CWColormap | CWEventMask                , // attributes set
        &swa                                      // attributes
    );

    if (!m_Window)
    {
        LOG(FAILURE, PLATFORM_CHANNEL, "Failed to create window.");
        exit(1);
    }

    XFree(vi);
    XStoreName(m_Display, m_Window, WindowName);
    XMapWindow(m_Display, m_Window);    

}

void Linux_Window::ProcessOSWindowMessages()
{
    if (m_Display == nullptr || m_Window == 0) 
    {
        LOG(FAILURE, PLATFORM_CHANNEL, "Not valid display or window");
        EnvironmentManager::Get()->ExecutionState(EExecutionState::EXIT);
    }

    XEvent Event;
    XWindowAttributes Attrs;

    while(XPending(m_Display) > 0)
    {
        XNextEvent(m_Display, &Event);

        switch(Event.type)
        {
            case Expose:
                XGetWindowAttributes(m_Display, m_Window, &Attrs);
                glViewport(0, 0, Attrs.width, Attrs.height);
                break;

            case KeyPress:
            case KeyRelease:
            {} break;

            case ConfigureNotify:
            {} break;

            case DestroyNotify:
            {
                EnvironmentManager::Get()->ExecutionState(EExecutionState::EXIT);
            } break;
        }
    }

}

void Linux_Window::SwapOpenGLBuffers()
{
    if (m_Display != nullptr && m_Window != 0)
    {
        glXSwapBuffers(m_Display, m_Window);
    }
}

IWindow* PlatformManager::CreateWindow(
        const int Width, const int Height, const char* WindowName)
{
    IWindow* Result = new Linux_Window;
    Result->Initialize(Width, Height, WindowName);
    return Result;
}

