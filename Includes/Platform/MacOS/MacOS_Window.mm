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
#include <Interfaces/Managers/IPlatformManager.h>
#include <Utility/PlatformDetection.h>

#include <Utility/Libs.h>
#include <Utility/Macro.h>
#include <Utility/Delegate.h>
#import <Utility/Logger.h>
#include <Engine/Managers/PlatformManager.h>
#include <Engine/Managers/EnvironmentManager.h>
#import <Cocoa/Cocoa.h>
#include "AppDelegate.h"


FNowTime* FLog::s_NowTime = nullptr;
FChangeConsoleColor* FLog::s_ChangeConsoleColor = nullptr;
int FLog::s_Verbosity = (int)ELogLevel::INFO;
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
    NSOpenGLContext*   m_OpenGLContext;

    virtual void Initialize(const int Width, const int Height, const char* WindowName) final;
    virtual void ProcessOSWindowMessages() final;
    virtual void SwapOpenGLBuffers() final;
    virtual void Setup() final;
};

@implementation WindowDelegate : NSObject
{

}
@end


@implementation AppDelegate : NSObject
- (void)applicationWillFinishLaunching:(NSNotification *)notification
{
    [window makeKeyAndOrderFront:self];
}
@end

@implementation WindowDelegate : NSObject

- (void)windowDidBecomeKey:(NSNotification *)notification 
{
}
- (void)windowDidBecomeMain:(NSNotification *)notification
{
}
- (void)windowDidResignKey:(NSNotification *)notification
{
}
- (void)windowDidResignMain:(NSNotification *)notification
{
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


void MacOS_Window::Initialize(const int Width, const int Height, const char* WindowName)
{
    NSUInteger windowStyle = NSWindowStyleMaskTitled  | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable | NSWindowStyleMaskMiniaturizable;
    NSRect screenRect = [[NSScreen mainScreen] frame];
    NSRect viewRect = NSMakeRect(0, 0, Width, Height);
    NSRect windowRect = NSMakeRect(NSMidX(screenRect) - NSMidX(viewRect),
                                   NSMidY(screenRect) - NSMidY(viewRect),
                                   viewRect.size.width,
                                   viewRect.size.height);
  
    m_Window = [[NSWindow alloc] initWithContentRect:windowRect
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
    m_WindowController = [[NSWindowController alloc] initWithWindow:m_Window];
    [m_WindowController autorelease];
    NSView* view = [[[NSView alloc] initWithFrame:viewRect] autorelease];
    [m_Window setContentView:view];
    WindowDelegate* windowDelegate = [[WindowDelegate alloc] init];
    [m_Window setDelegate:windowDelegate];   
    [m_Window setAcceptsMouseMovedEvents:YES];
    [m_Window setTitle:[NSString stringWithUTF8String:WindowName]];
    [m_Window setCollectionBehavior: NSWindowCollectionBehaviorFullScreenPrimary];
    [m_Window makeKeyAndOrderFront:nil];
}


void MacOS_Window::ProcessOSWindowMessages()
{
    @autoreleasepool {
        NSEvent* ev;
        do {
            ev = [NSApp nextEventMatchingMask: NSEventMaskAny
                                    untilDate: nil
                                       inMode: NSDefaultRunLoopMode
                                      dequeue: YES];
            if (ev) {
                switch (ev.type)
                {
                    case NSEventTypeLeftMouseDown:
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




    




