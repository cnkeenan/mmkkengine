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
uint64 FLog::s_Channels = 0xFFFFFFFFFFFFFFFF;
FLog::FLogFile FLog::s_ChannelFiles[NUMBER_OF_CHANNELS] = {};
FILE* FLog::s_LogDump = nullptr;
const char* FLog::RESERVED_CHANNEL_PATH =  "../Data/Log/Reserved_Log/Reserved.log";
const char* FLog::ENGINE_CHANNEL_PATH = "../Data/Log/Engine_Log/Engine.log";
const char* FLog::PLATFORM_CHANNEL_PATH = "../Data/Log/Platform_Log/Platform.log";
const char* FLog::DUMP_PATH = "../Data/Log/Dump.log";        
IMutex* FLog::s_Mutex = nullptr;

struct MacOS_Window : public IWindow 
{
    NSWindow* m_Window;
    NSWindowController* m_WindowController;

    virtual void Initialize(const int Width, const int Height, const char* WindowName) final;
    virtual void ProcessOSWindowMessages() final;
    virtual void SwapOpenGLBuffers() final;
    virtual void Setup() final;
};


@implementation AppDelegate : NSObject

- (void)applicationWillFinishLaunching:(NSNotification *)notification
{
    [window makeKeyAndOrderFront:self];
}

@end

@implementation WindowDelegate : NSObject

- (void)windowDidBecomeKey:(NSNotification *)notification 
{
    NSLog(@"Window: become key");
}

- (void)windowDidBecomeMain:(NSNotification *)notification
{
    NSLog(@"Window: become main");
}
- (void)windowDidResignKey:(NSNotification *)notification
{
    NSLog(@"Window: resign key");
}
- (void)windowDidResignMain:(NSNotification *)notification
{
    NSLog(@"Window: resign main");
}

-(void)windowWillClose:(NSNotification *)notification 
{
    NSWindow* window = notification.object;
    if (window.isMainWindow)
    {
        EnvironmentManager::Get()->ExecutionState(EExecutionState::EXIT);
    }
}  

@end

void MacOS_Window::Setup()
{
    // [NSApplication sharedApplication];
    
    // AppDelegate* appDelegate = [[AppDelegate alloc] init];
    // [NSApp setDelegate:appDelegate];
    
    // [NSApp finishLaunching];
}

void MacOS_Window::Initialize(const int Width, const int Height, const char* WindowName)
{
    // Setup();

    NSUInteger windowStyle = NSWindowStyleMaskTitled  | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable | NSWindowStyleMaskMiniaturizable;
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
    WindowDelegate* windowDelegate = [[WindowDelegate alloc] init];
    [window setDelegate:windowDelegate];   
    [window setAcceptsMouseMovedEvents:YES];
    [window setTitle:[NSString stringWithUTF8String:WindowName]];
    [window setCollectionBehavior: NSWindowCollectionBehaviorFullScreenPrimary];
    [window makeKeyAndOrderFront:nil];
}


void MacOS_Window::ProcessOSWindowMessages()
{
    @autoreleasepool {
        NSEvent* ev;
        do {
            ev = [NSApp nextEventMatchingMask: NSAnyEventMask
                                    untilDate: nil
                                       inMode: NSDefaultRunLoopMode
                                      dequeue: YES];
            if (ev) {
                switch (ev.type)
                {
                    case NSEventTypeLeftMouseDown:
                        NSLog(@"Left Mouse Button Down");
                        break;
                    default:
                        break;
                }
                [NSApp sendEvent: ev];
            }
        } while (ev);
    }
}

void MacOS_Window::SwapOpenGLBuffers()
{
   // [glContext flushBuffer];
}

IWindow* PlatformManager::CreateWindow(const int Width, const int Height, const char* WindowName)
{
    IWindow* Result = new MacOS_Window;
    Result->Initialize(Width, Height, WindowName);
    return Result;
}




    




