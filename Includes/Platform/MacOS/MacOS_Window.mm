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
#include <Utility/PlatformDetection.h>
#import <Utility/Logger.h>
#include <Engine/Managers/PlatformManager.h>
#include <Engine/Managers/EnvironmentManager.h>
#import <Cocoa/Cocoa.h>
#include "AppDelegate.h"


FNowTime* FLog::NowTime = nullptr;
FChangeConsoleColor* FLog::ChangeConsoleColor = nullptr;
int FLog::Verbosity = (int)ELogLevel::INFO;


@implementation AppDelegate : NSObject

- (void)applicationWillFinishLaunching:(NSNotification *)notification
{
    [window makeKeyAndOrderFront:self];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender
{
    EnvironmentManager::Get()->ExecutionState(EExecutionState::EXIT);
    return YES;
}

@end

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
    [NSApplication sharedApplication];
    
    AppDelegate* appDelegate = [[AppDelegate alloc] init];
    [NSApp setDelegate:appDelegate];
    
    [NSApp finishLaunching];

    NSUInteger windowStyle = NSTitledWindowMask  | NSClosableWindowMask | NSResizableWindowMask | NSMiniaturizableWindowMask;
    
    NSRect screenRect = [[NSScreen mainScreen] frame];
    NSRect viewRect = NSMakeRect(0, 0, Width, Height);
    NSRect windowRect = NSMakeRect(NSMidX(screenRect) - NSMidX(viewRect),
                                   NSMidY(screenRect) - NSMidY(viewRect),
                                   viewRect.size.width,
                                   viewRect.size.height);
    
    NSWindow* window = [[NSWindow alloc] initWithContentRect:windowRect
                                                    styleMask:windowStyle
                                                      backing:NSBackingStoreBuffered
                                                        defer:NO];
    
    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
    
    id menubar = [[NSMenu new] autorelease];
    id appMenuItem = [[NSMenuItem new] autorelease];
    [menubar addItem:appMenuItem];
    [NSApp setMainMenu:menubar];
    
    id appMenu = [[NSMenu new] autorelease];
    id appName = [[NSProcessInfo processInfo] processName];
    id quitTitle = [@"Quit " stringByAppendingString:appName];
    id quitMenuItem = [[[NSMenuItem alloc] initWithTitle:quitTitle
                                                  action:@selector(terminate:) keyEquivalent:@"q"] autorelease];
    [appMenu addItem:quitMenuItem];
    [appMenuItem setSubmenu:appMenu];
    
    NSWindowController * windowController = [[NSWindowController alloc] initWithWindow:window];
    [windowController autorelease];
    
    NSView* view = [[[NSView alloc] initWithFrame:viewRect] autorelease];
    [window setContentView:view];

    //Window Delegate
    // NSWindowDelegate* windowDelegate = [[NSWindowDelegate alloc] init];
    // [window setDelegate:windowDelegate];
    
    [window setAcceptsMouseMovedEvents:YES];
    //[window setDelegate:view];
    
    // Set app title
    [window setTitle:[NSString stringWithUTF8String:WindowName]];
    
    // Add fullscreen button
    [window setCollectionBehavior: NSWindowCollectionBehaviorFullScreenPrimary];
    [window makeKeyAndOrderFront:nil];



    // NSApplication* application = [NSApplication sharedApplication];
    // AppDelegate* appDelegate = [[[AppDelegate alloc ] init] autorelease];

    // NSRect frame = NSMakeRect(0, 0, Width, Height);
    //     NSWindow* window = [[NSWindow alloc] initWithContentRect:frame
    //                                          styleMask:NSWindowStyleMaskClosable | NSWindowStyleMaskTitled | NSWindowStyleMaskResizable
    //                                             backing:NSBackingStoreBuffered
    //                                               defer:NO];
        
    
    // [window setTitle:[NSString stringWithUTF8String:WindowName]];
    // [window makeKeyAndOrderFront: nil];
    // [window setBackgroundColor:[NSColor blueColor]];
    // [application setDelegate:appDelegate];
    // [application run];


}


void MacOS_Window::ProcessOSWindowMessages()
{
    NSEvent* event;
    do 
    {
        event = [NSApp nextEventMatchingMask:NSAnyEventMask 
                    untilDate:[NSDate distantPast] 
                    inMode:NSDefaultRunLoopMode 
                    dequeue:YES];
        printf("Test\n");

        [NSApp sendEvent: event];
    }
    while (event != nil);
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




    




