#ifndef _LINUX_Window_H
#define _LINUX_Window_H

#include "Linux.h"

//TODO: better logging
//TODO: find out what other events we need to handle
//TODO: actually handle xevents 

struct Linux_Window : public IWindow
{
    Display      m_Xdisplay;
    Window       m_RootWindow;
    Window       m_Window;
    GLXContext   m_RenderingContext;

    virtual void Initialize(
                    const int Width, const int Height, const char* WindowName);
    virtual bool ProcessOSWindowMessages() final;
    virtual void SwapOpenGLBuffers() final;
}


void Linux_Window::Initialize(
            const int Width, const int Height, const char* WindowName)
{
    Colormap               colormap;
    XVisualInfo            *visual_info;
    XSetWindowAttributes   set_xwindow_attrs;
    XWindowAttributes      xwindow_attrs;

    GLXContext             glcontext;
    GLint attrs[] = 
    {
        GLX_RGBA         ,
        GLX_DEPTH_SIZE   ,
        24               ,
        GLX_DOUBLEBUFFER ,
        None
    };

    m_Xdisplay = XOpenDisplay(NULL);
    if (m_Xdisplay == NULL) 
    {
        printf("[FATAL] Cannot connect to X Server.\n");                
        exit(0);
    }


    visual_info = glXChooseVisual(m_Xdisplay, 0, attrs);
    if (visual_info == NULL)
    {
        printf("[FATAL] No appropriate visual found.");
        exit(0);
    }

    m_RootWindow = DefaultRootWindow(m_Xdisplay);

    colormap = XCreateColormap(
        m_Xisplay           ,
        m_RootWindow        ,
        visual_info->visual ,
        AllocNone
    );
    set_xwindow_attrs.colormap = colormap;
    set_xwindow_attrs.event_mask = ExposureMask | KeyPressMask;

    m_Window = XCreateWindow(
        m_Xdisplay,
        m_RootWindow,
        0,
        0,
        Width,
        Height,
        0,
        visual_info->depth,
        InputOutput,
        visual_info->visual,
        CWColormap | CWEventMask,
        &set_xwindow_attrs
    );

    XMapWindow(m_Display, m_Window);
    XStoreName(m_Display, m_Window, WindowName);

    m_RenderingContext = glXCreateContext(
        ActualWindow->m_Display ,
        visual_info             ,
        NULL                    ,
        GL_TRUE
    );
    glXMakeCurrent(m_Display, m_Window, m_RenderingContext);
    glEnable(GL_DEPTH_TEST);
}

bool Linux_Window::ProcessOSWindowMessages()
{
    XEvent xevent;
    XWindowAttributes attrs;

    while(1) {

        XNextEvent(m_Xdisplay, &xevent);

        switch(xevent.type) 
        {
            case Expose:
                printf("[INFO] Expose");
                break;
            case KeyPress:
                printf("[INFO] KeyPress");
                break;
            default:
                break;
        }

    }

    return false;
}

void Linux_Window::SwapOpenGLBuffers()
{
    if (m_Display != NULL && m_Window != NULL)
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

#endif
