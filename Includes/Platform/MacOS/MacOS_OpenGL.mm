void PlatformManager::InitializeOpenGLContext(IWindow *Window)
{
    NSOpenGLPixelFormatAttribute pixelFormatAttributes[] =
{
    NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
    NSOpenGLPFAColorSize    , 24                           ,
    NSOpenGLPFAAlphaSize    , 8                            ,
    NSOpenGLPFADoubleBuffer ,
    NSOpenGLPFAAccelerated  ,
    0
};
// NSOpenGLPixelFormat *pixelFormat = [[[NSOpenGLPixelFormat alloc] initWithAttributes:pixelFormatAttributes] autorelease];
// [self setView:[[[NSOpenGLView alloc] initWithFrame:[[[self window] contentView] bounds] pixelFormat:pixelFormat] autorelease]];
// [[[self window] contentView] addSubview:[self view]];
  
}
