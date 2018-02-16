void PlatformManager::InitializeOpenGLContext(IWindow *Window)
{
    MacOS_Window* macWin = (MacOS_Window*)Window;
    NSOpenGLPixelFormatAttribute pixelAttrs[] = {
        NSOpenGLPFADoubleBuffer,
        NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
        NSOpenGLPFAColorSize, 24,
        NSOpenGLPFAAlphaSize, 8,
        NSOpenGLPFADepthSize, 24,
        0,
    };

    NSOpenGLPixelFormat* pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:pixelAttrs];

    NSOpenGLContext* glContext = [[NSOpenGLContext alloc]
                                  initWithFormat:pixelFormat
                                  shareContext:NULL];
    macWin->m_OpenGLView = [[[CustomOpenGLView alloc] initWithFrame:macWin->m_Bounds pixelFormat:pixelFormat] autorelease];
    [macWin->m_OpenGLView setOpenGLContext: glContext];
}
