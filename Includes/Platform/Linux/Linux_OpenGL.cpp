#define GLX_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB 0x2092

typedef GLXContext(*glXCreateContextAttribsARBProc)
    (Display*, GLXFBConfig, GLXContext, Bool, const int*);

static bool ctxErrorOccurred = False;


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

void PlatformManager::InitializeOpenGLContext(IWindow *Window) {

    Linux_Window* win = (Linux_Window*)Window;

    const char* glxExts = glXQueryExtensionsString(
            win->m_Display,
            DefaultScreen(win->m_Display)
    ); 

    glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
    glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)
        glXGetProcAddressARB((const GLubyte*) "glXCreateContextAttribsARB");

    win->m_RenderingContext = 0;
    ctxErrorOccurred = False;

    int (*oldHandler) (Display*, XErrorEvent*) = XSetErrorHandler(&ctxErrorHandler);

    if (!isExtensionSupported(glxExts, "GLX_ARB_create_context") ||
            !glXCreateContextAttribsARB)
    {
        LOG(INFO, PLATFORM_CHANNEL, "glXCreateContextAttribsARB() not found.");
        win->m_RenderingContext = glXCreateNewContext(
                win->m_Display,
                win->tmp_GLFBConfig,
                GLX_RGBA_TYPE,
                0,
                True
        );
    }
    else
    {
        int context_attrs[] =
        {
            GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
            GLX_CONTEXT_MINOR_VERSION_ARB, 3,
            None
        };
        win->m_RenderingContext = glXCreateContextAttribsARB(
            win->m_Display     ,
            win->tmp_GLFBConfig,
            0             ,
            True          ,
            context_attrs
        );

        LoadOpenGL_1_0(Linux_GetGLFunction);

        XSync(win->m_Display, False);

        if (!ctxErrorOccurred && win->m_RenderingContext)
        {
            LOG(INFO, PLATFORM_CHANNEL, "Created GL 3.3 Context");
            LoadOpenGL_3_3(Linux_GetGLFunction);
        }
        else
        {
            context_attrs[1] = 1;
            context_attrs[3] = 0;
            ctxErrorOccurred = False;

            LOG(INFO, PLATFORM_CHANNEL, "Failed to create GL 3.0 Context");

            win->m_RenderingContext = glXCreateContextAttribsARB(
                win->m_Display     ,
                win->tmp_GLFBConfig,
                0             ,
                True          ,
                context_attrs
            );

        }
    }

    XSync(win->m_Display, false);
    XSetErrorHandler(oldHandler);

    if (ctxErrorOccurred || !win->m_RenderingContext)
    {
        LOG(FAILURE, PLATFORM_CHANNEL, "Failed to create OpenGL Context");
        exit(1);
    }

    if (!glXIsDirect(win->m_Display, win->m_RenderingContext))
    {
        LOG(INFO, PLATFORM_CHANNEL, "Indirect GLX Rendering Context obtained");
    }
    else
    {
        LOG(INFO, PLATFORM_CHANNEL, "Direct GLX Rendering Context obtained");
    }

    glXMakeCurrent(win->m_Display, win->m_Window, win->m_RenderingContext);
}

