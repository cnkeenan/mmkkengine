/*
 * File: MacOS_Window.m
 *
 * Brief:
 *  Creates a OSX/Cocoa application and window without Interface Builder or XCode.
 *
 * Compile with:
 *  gcc MacOS_Window.m -o  -framework Cocoa
 */

#import "MacOS.h"
#import "Cocoa/Cocoa.h"


@implementation MacOS_Window : public IWindow
{
    //Display      m_Xdisplay;
    // Window       m_RootWindow;
    // Window       m_Window;
    //GLXContext   m_RenderingContext;

    virtual void Initialize(
                    const int Width, const int Height, const char* WindowName) final;
    virtual bool ProcessOSWindowMessages() final;
    virtual void SwapOpenGLBuffers() final;
    virtual ~MacOS_Window() {}
    // virtual FHighResolutionTimer CreateHighResolutionTimer() final;

};

void MacOS_Window::Initialize(const int Width, const int Height, const char* WindowName)
{
    // Autorelease Pool:
    // Objects declared in this scope will be automatically
    // released at the end of it, when the pool is "drained".
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];

    // Create a shared app instance.
    // This will initialize the global variable
    // 'NSApp' with the application instance.
    [NSApplication sharedApplication];

    //
    // Create a window:
    //

    // Style flags:
    NSUInteger windowStyle = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable;

    // Window bounds (x, y, width, height).
    NSRect windowRect = NSMakeRect(100, 100, Width, Height);
    NSWindow * window = [[NSWindow alloc] initWithContentRect:windowRect
                                          styleMask:windowStyle
                                          backing:NSBackingStoreBuffered
                                          defer:NO];
    [window autorelease];

    // Window controller:
    NSWindowController * windowController = [[NSWindowController alloc] initWithWindow:window];
    [windowController autorelease];



    // TODO: Create app delegate to handle system events.
    // TODO: Create menus (especially Quit!)

    // Show window and run event loop.
    [window orderFrontRegardless];
    [NSApp run];

    [pool drain];
}

bool MacOS_Window::ProcessOSWindowMessages()
{
    return false;
}

void MacOS_Window::SwapOpenGLBuffers()
{

}

IWindow* PlatformManager::CreateWindow(
        const int Width, const int Height, const char* WindowName)
{
    IWindow* Result = new MacOS_Window;
    Result->Initialize(Width, Height, WindowName);
    return Result;
}



