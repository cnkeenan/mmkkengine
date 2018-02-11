/*
 * File: MacOS_Window.m
 *
 * Brief:
 *  Creates a OSX/Cocoa application and window without Interface Builder or XCode.
 *
 * Compile with:
 *  gcc MacOS_Window.m -o a -framework Cocoa
 */

#include <Utility/AtomicTypes.h>
#include <Utility/Logger.h>
#include <Engine/Managers/PlatformManager.h>
#include <Engine/Managers/EnvironmentManager.h>
#import <Cocoa/Cocoa.h>

struct MacOS_Window : public IWindow 
{
    NSWindow* m_Window;
    NSWindowController* m_WindowController;

    virtual void Initialize(const int Width, const int Height, const char* WindowName) final;
    virtual void ProcessOSWindowMessages() final;
    virtual void SwapOpenGLBuffers() final;
};



void MacOS_Window::Initialize(const int Width, const int Height, const char* WindowName)
{
    // Autorelease Pool:
    // Objects declared in this scope will be automatically
    // released at the end of it, when the pool is "drained".
    //NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];

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
    NSRect windowRect = NSMakeRect(0, 0, Width, Height);
    m_Window = [[NSWindow alloc] initWithContentRect:windowRect
                                          styleMask:windowStyle
                                          backing:NSBackingStoreBuffered
                                          defer:NO];
    [m_Window autorelease];

    // Window controller:
    m_WindowController = [[NSWindowController alloc] initWithWindow:m_Window];
    [m_WindowController autorelease];

    [m_Window setTitle:[NSString stringWithUTF8String:WindowName]];
    // TODO: Create app delegate to handle system events.

    
    // TODO: Create menus (especially Quit!)

    // Show window and run event loop.
    [m_Window orderFrontRegardless];
    [NSApp run];
    
    

    //[pool drain];
}

@interface WindowDelegate : NSObject 
{
    NSWindow* m_window;
}

- (instancetype)initWithWindow:(NSWindow* )initWindow;

@end


@implementation WindowDelegate

- (instancetype)initWithWindow:(NSWindow* )initWindow 
{
    self = [super init];
    if (self != nil)
        m_window = initWindow;
    return self;
}

-(BOOL)windowShouldClose:(id)sender
{
    EnvironmentManager::Get()->ExecutionState(EExecutionState::EXIT);
    return NO;
}

@end 

void MacOS_Window::ProcessOSWindowMessages()
{
    NSEvent *event = [NSApp nextEventMatchingMask:NSEventMaskAny 
                            untilDate:nil 
                            inMode:NSDefaultRunLoopMode 
                            dequeue:YES];

                
    switch([(NSEvent *)event type])
    {
        case NSEventTypeKeyDown:
            NSLog (@"Hello, World!");
            break;
        
        
        default:
            [NSApp sendEvent:event];
            break;
    }

    
    [event release];


    
}

void MacOS_Window::SwapOpenGLBuffers()
{

}

IWindow* PlatformManager::CreateWindow(const int Width, const int Height, const char* WindowName)
{
    IWindow* Result = new MacOS_Window;
    Result->Initialize(Width, Height, WindowName);
    return Result;
}




    




