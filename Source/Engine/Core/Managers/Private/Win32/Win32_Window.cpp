/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#include "Win32.h"

struct Win32_Window : public IWindow
{
    HWND m_Window;
    HDC m_DeviceContext;
    HGLRC m_RenderingContext;

    virtual void Initialize(const int Width, const int Height, const char* WindowName) final;
    virtual bool ProcessOSWindowMessages() final;
    virtual void SwapOpenGLBuffers() final;
};



static LRESULT CALLBACK Win32_WindowProcedure(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{
    LRESULT Result = 0;

    switch(Message)
    {
        case WM_CLOSE:
        {
            PostQuitMessage(0);
        } break;

        default:
        {
            Result = DefWindowProc(Window, Message, WParam, LParam);
        } break;
    }
    
    return Result;
}

//NOTE(EVERYONE): We want the width and height to be the size of the client area not the window resolution.
//That is just a little bit bigger because of the padding.
void Win32_Window::Initialize(const int Width, const int Height, const char* WindowName)
{
    WNDCLASSEX WindowClass = {};
    WindowClass.cbSize = sizeof(WNDCLASSEX);
    WindowClass.hInstance = GetModuleHandle(0);
    WindowClass.style = CS_HREDRAW|CS_VREDRAW|CS_OWNDC;
    WindowClass.lpszClassName = WindowName;
    WindowClass.lpfnWndProc = Win32_WindowProcedure;

    if(RegisterClassEx(&WindowClass))
    {        
        RECT ClientRect{0, 0, Width, Height};
        DWORD Style = WS_OVERLAPPEDWINDOW;
        BOOL Result = AdjustWindowRectEx(&ClientRect, Style, FALSE, 0);
        if(Result)
        {
            m_Window = CreateWindow(WindowName, WindowName, Style, CW_USEDEFAULT, CW_USEDEFAULT,
                                    ClientRect.right-ClientRect.left, ClientRect.bottom-ClientRect.top,
                                    0, 0, WindowClass.hInstance, 0);
            if(m_Window)
            {
                ShowWindow(m_Window, SW_SHOW);
            }
            else
            {
                //TODO(JJ): Logging
            }
        }
        else
        {
            //TODO(JJ): Logging 
        }
    }
    else
    {
        //TODO(JJ): Logging
    }
}

bool Win32_Window::ProcessOSWindowMessages()
{
    bool Result = false;
    
    MSG Message;
    while(PeekMessage(&Message, 0, 0, 0, PM_REMOVE))
    {
        switch(Message.message)
        {
            case WM_QUIT:
            {
                Result = true;
            } break;

            default:
            {
                TranslateMessage(&Message);
                DispatchMessage(&Message);
            } break;
        }
    }

    return Result;
}

void Win32_Window::SwapOpenGLBuffers()
{
    if(m_DeviceContext)
        SwapBuffers(m_DeviceContext);
}

#undef CreateWindow
IWindow* PlatformManager::CreateWindow(const int Width, const int Height, const char* WindowName)
{
    IWindow* Result = new Win32_Window;
    Result->Initialize(Width, Height, WindowName);
    return Result;
}
