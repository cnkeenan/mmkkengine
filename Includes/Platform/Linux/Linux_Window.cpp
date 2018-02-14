#define GLX_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB 0x2092

typedef GLXContext(*glXCreateContextAttribsARBProc)
    (Display*, GLXFBConfig, GLXContext, Bool, const int*);

static bool ctxErrorOccurred = False;

struct Linux_Window : public IWindow
{
    Display*     m_Display; /* access to X Server */
    Window       m_Window;
    GLXContext   m_RenderingContext;

    virtual void Initialize(
                    const int Width, const int Height, const char* WindowName);
    virtual void ProcessOSWindowMessages() final;
    virtual void SwapOpenGLBuffers() final;
};


static int ctxErrorHandler(Display *dpy, XErrorEvent *ev)
{
    ctxErrorOccurred = True;
    return 0;
}

static bool isExtensionSupported(const char* extList, const char* extension)
{
    const char *start;
    const char *where, *terminator;

    where = strchr(extension, ' ');

    if (where || *extension == '\0')
    {
        return False;
    }

    for (start=extList;;)
    {
        where = strstr(start, extension);
        if (!where)
        {
            break;
        }

        terminator = where + strlen(extension);

        if (where == start || *(where - 1) == ' ')
        {
            if (*terminator == ' ' || *terminator == '\0')
            {
                return True;
            }
        }
        start = terminator;
    }

    return False;
}



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

    GLXFBConfig bestFbc = fbc[best_fbc];
    XFree(fbc);

    XVisualInfo *vi = glXGetVisualFromFBConfig(m_Display, bestFbc);
    cmap = XCreateColormap(
            m_Display                          ,
            RootWindow(m_Display , vi->screen) ,
            vi->visual                         ,
            AllocNone
    );

    swa.colormap = cmap;
    swa.background_pixmap = None;
    swa.border_pixel = 0;
    swa.event_mask =  StructureNotifyMask | ExposureMask | KeyPressMask;

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

    const char *glxExts = glXQueryExtensionsString(
        m_Display,
        DefaultScreen(m_Display)
    );

    glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
    glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc) 
        glXGetProcAddressARB((const GLubyte *) "glXCreateContextAttribsARB");

    m_RenderingContext = 0;

    ctxErrorOccurred = False;

    int (*oldHandler) (Display*, XErrorEvent*) = XSetErrorHandler(&ctxErrorHandler);

    if (!isExtensionSupported(glxExts, "GLX_ARB_create_context") ||
            !glXCreateContextAttribsARB)
    {
        LOG(INFO, "glXCreateContextAttribsARB() not found.");
        m_RenderingContext = glXCreateNewContext(
            m_Display     ,
            bestFbc       ,
            GLX_RGBA_TYPE ,
            0             ,
            True
        );
         
    }
    else
    {
        //NOTE(Ray): I (JJ) change this to target 3.3
        int context_attrs[] =
        {
            GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
            GLX_CONTEXT_MINOR_VERSION_ARB, 3,
            None
        };
        m_RenderingContext = glXCreateContextAttribsARB(
            m_Display     ,
            bestFbc       ,
            0             ,
            True          ,
            context_attrs
        );

        XSync(m_Display, False);

        if (!ctxErrorOccurred && m_RenderingContext)
        {
            LOG(INFO, PLATFORM_CHANNEL, "Creating GL 3.3 Context");
        }
        else
        {
            context_attrs[1] = 1;
            context_attrs[3] = 0;
            ctxErrorOccurred = False;

            LOG(INFO, "Failed to create GL 3.0 Context");

            m_RenderingContext = glXCreateContextAttribsARB(
                m_Display     ,
                bestFbc       ,
                0             ,
                True          ,
                context_attrs
            );
            
        }
    }

    XSync(m_Display, False);
    XSetErrorHandler(oldHandler);

    if (ctxErrorOccurred || !m_RenderingContext)
    {
        LOG(FAILURE, PLATFORM_CHANNEL, "Failed to create OpenGL Context");
        exit(1);
    }

    if (!glXIsDirect(m_Display, m_RenderingContext))
    {
        LOG(INFO, PLATFORM_CHANNEL, "Indirect GLX Rendering Context obtained");
    }
    else
    {
        LOG(INFO, PLATFORM_CHANNEL, "Direct GLX Rendering Context obtained");
    }

    glXMakeCurrent(m_Display, m_Window, m_RenderingContext);

}

void Linux_Window::ProcessOSWindowMessages()
{
    //TODO: fix this implementation
    if (m_Display == nullptr || m_Window == 0) 
    {
        LOG(FAILURE, "Not valid display or window");
        EnvironmentManager::Get()->ExecutionState(EExecutionState::EXIT);
    }

    XEvent xevent;
    XWindowAttributes attrs;


    XPeekEvent(m_Display, &xevent);

    switch(xevent.type) 
    {
        case Expose:
            LOG(INFO, "Expose event");
            XGetWindowAttributes(m_Display, m_Window, &attrs);
            glViewport(0, 0, attrs.width, attrs.height);
            break;

        case KeyPress:
            LOG(INFO, "Key press event");
            break;

        default:
            break;
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

