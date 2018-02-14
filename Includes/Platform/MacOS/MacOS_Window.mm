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

@implementation AppDelegate : NSObject

- (void)applicationWillFinishLaunching:(NSNotification *)notification
{
    [window makeKeyAndOrderFront:self];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender
{
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
    
    NSApplication* application = [NSApplication sharedApplication];
    AppDelegate* appDelegate = [[[AppDelegate alloc ] init] autorelease];

    NSRect frame = NSMakeRect(0, 0, Width, Height);
    NSWindow* window = [[NSWindow alloc] initWithContentRect:frame
                                                   styleMask:NSWindowStyleMaskClosable | NSWindowStyleMaskTitled | NSWindowStyleMaskResizable
                                                     backing:NSBackingStoreBuffered
                                                       defer:NO];
        
    
    [window setTitle:[NSString stringWithUTF8String:WindowName]];
    [window makeKeyAndOrderFront: nil];
    [window setBackgroundColor:[NSColor blueColor]];
    // NSLog(@"Test");
    [application setDelegate:appDelegate];
    [application run];


}


void MacOS_Window::ProcessOSWindowMessages()
{
    bool quit = true;
    
    while (!quit) {
        NSLog(@"Entered Loop");
        NSEvent* event = [NSApp nextEventMatchingMask:NSEventMaskAny 
                                    untilDate:nil 
                                    inMode:NSDefaultRunLoopMode 
                                    dequeue:YES];
        switch([(NSEvent* )event type])
        {
            case NSEventTypeLeftMouseDown:
                NSLog(@"NSEventTypeLeftMouseDown");
                quit = true;
                break;
            default:
                [NSApplication sendEvent:event];
                break;
        }
        [event release];
    }
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




    




