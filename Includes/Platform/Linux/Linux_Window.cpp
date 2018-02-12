//TODO: better logging
//TODO: find out what other events we need to handle
//TODO: actually handle xevents 
//TODO: add a state variable to check if initialization was successful
//TODO: handle all possible errors using X error handlers

struct Linux_Window : public IWindow
{
    Display*     m_Display; /* access to X Server */
    Window       m_RootWindow;
    Window       m_Window;
    GLXContext   m_RenderingContext;

    virtual void Initialize(
                    const int Width, const int Height, const char* WindowName);
    virtual void ProcessOSWindowMessages() final;
    virtual void SwapOpenGLBuffers() final;
};

void Linux_Window::Initialize(
            const int Width, const int Height, const char* WindowName)
{
    XVisualInfo *vi;
    GLint attrs[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};

    XSetWindowAttributes swa;
    Colormap cmap;

    m_Display = XOpenDisplay(nullptr);
    if (m_Display == nullptr) 
    {
        exit(-1);
    }

    m_RootWindow = DefaultRootWindow(m_Display);

    // TODO: separate into another function to check different combinations
    // to account for different hardware support
    vi = glXChooseVisual(m_Display, 0, attrs);
    if (vi == nullptr)
    {
        std::cout << "[FATAL] No appropriate visual found.\n";
        exit(-1);
    }

    cmap = XCreateColormap(m_Display, m_RootWindow, vi->visual, AllocNone);
    swa.colormap = cmap;
    swa.event_mask = ExposureMask | KeyPressMask;

    m_Window = XCreateWindow(
        m_Display                ,
        m_RootWindow             ,
        0                        , // x position
        0                        , // y position
        Width                    ,
        Height                   ,
        0                        , // border width
        vi->depth                , // depth
        InputOutput              , // window class
        vi->visual               ,
        CWColormap | CWEventMask , // attributes set
        &swa                       // attributes
    );

    XMapWindow(m_Display, m_Window);
    XStoreName(m_Display, m_Window, WindowName);

    m_RenderingContext = glXCreateContext(m_Display, vi, nullptr, GL_TRUE);
    glXMakeCurrent(m_Display, m_Window, m_RenderingContext);

}

void Linux_Window::ProcessOSWindowMessages()
{
    if (m_Display == nullptr || m_Window == 0) 
    {
        std::cout << "[WARNING] Not valid Display or Window.\n";
        EnvironmentManager::Get()->ExecutionState(EExecutionState::EXIT);
    }

    XEvent xevent;
    XWindowAttributes attrs;

    while(1) {

        XNextEvent(m_Display, &xevent);

        switch(xevent.type) 
        {
            case Expose:
                std::cout << "[INFO] Expose\n";

                XGetWindowAttributes(m_Display, m_Window, &attrs);
                glViewport(0, 0, attrs.width, attrs.height);
                break;

            case KeyPress:
                std::cout << "[INFO] KeyPress\n";
                break;

            default:
                break;
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

