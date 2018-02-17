#ifndef _LINUX_H
#define _LINUX_H

#include <dlfcn.h>
#include <X11/Xlib.h>
#include <dlfcn.h>
#include <iostream>

#define GLX_X_RENDERABLE   0x8012
#define GLX_DRAWABLE_TYPE  0x8010
#define GLX_WINDOW_BIT     0x00000001
#define GLX_RENDER_TYPE    0x8011
#define GLX_RGBA_BIT       0x00000001
#define GLX_X_VISUAL_TYPE  0x22
#define GLX_TRUE_COLOR     0x8002
#define GLX_RED_SIZE	   8
#define GLX_GREEN_SIZE	   9
#define GLX_BLUE_SIZE	   10
#define GLX_ALPHA_SIZE	   11
#define GLX_DEPTH_SIZE	   12
#define GLX_STENCIL_SIZE   13
#define GLX_DOUBLEBUFFER   5
#define GLX_RGBA_TYPE      0x8014
#define GLX_SAMPLE_BUFFERS 0x186a0
#define GLX_SAMPLES        0x186a1

typedef void (*__GLXextFuncPtr)(void);

typedef struct {
    Visual* visual;
    VisualID visualid;
    int screen;
    int depth;
    int clas;
    unsigned long red_mask;
    unsigned long green_mask;
    unsigned long blue_mask;
    int colormap_size;
    int bits_per_rgb;
} XVisualInfo;

typedef XID GLXDrawable;

typedef struct __GLXFBConfigRec *GLXFBConfig;
typedef struct __GLXcontextRec *GLXContext;
typedef int fp_glXGetFBConfigAttrib(Display*, GLXFBConfig, int, int*);
typedef __GLXextFuncPtr fp_glXGetProcAddressARB (const GLubyte *);
typedef Bool fp_glXQueryVersion(Display*, int*, int*);
typedef GLXFBConfig* fp_glXChooseFBConfig(Display*, int, const int*, int*);
typedef XVisualInfo* fp_glXGetVisualFromFBConfig(Display*, GLXFBConfig);
typedef void fp_glXSwapBuffers(Display*, GLXDrawable);
typedef const char* fp_glXQueryExtensionsString(Display*, int);
typedef GLXContext fp_glXCreateNewContext(Display*, GLXFBConfig, int, GLXContext, Bool);
typedef Bool fp_glXIsDirect(Display*, GLXContext);
typedef Bool fp_glXMakeCurrent(Display*, GLXDrawable, GLXContext);
typedef void fp_glViewport(GLint x, GLint y, GLsizei width, GLsizei height);

void* Linux_GetFunction(const char* Name)
{
    void* libGL = dlopen("libGL.so", RTLD_LAZY);
    return (void*)dlsym(libGL, Name);
}

FUNCTION_SIGNATURE(glXGetProcAddressARB) = (fp_glXGetProcAddressARB*)Linux_GetFunction("glXGetProcAddressARB");

void* Linux_GetGLFunction(const char* Name)
{
    void* p = (void*)glXGetProcAddressARB((const GLubyte*)Name);

    if(!p)
    {
        void* libGL = dlopen("libGL.so", RTLD_LAZY);
        p = (void*)dlsym(libGL, Name);
    }

    return p;
}

FUNCTION_SIGNATURE(glXQueryVersion) = (fp_glXQueryVersion*)Linux_GetGLFunction("glXQueryVersion");
FUNCTION_SIGNATURE(glXChooseFBConfig) = (fp_glXChooseFBConfig*)Linux_GetGLFunction("glXChooseFBConfig");
FUNCTION_SIGNATURE(glXGetVisualFromFBConfig) = (fp_glXGetVisualFromFBConfig*) Linux_GetGLFunction("glXGetVisualFromFBConfig");
FUNCTION_SIGNATURE(glXSwapBuffers) = (fp_glXSwapBuffers*)Linux_GetGLFunction("glXSwapBuffers");
FUNCTION_SIGNATURE(glXQueryExtensionsString) = (fp_glXQueryExtensionsString*)Linux_GetGLFunction("glXQueryExtensionsString");
FUNCTION_SIGNATURE(glXCreateNewContext) = (fp_glXCreateNewContext*)Linux_GetGLFunction("glXCreateNewContext");
FUNCTION_SIGNATURE(glXIsDirect) = (fp_glXIsDirect*)Linux_GetGLFunction("glXIsDirect");
FUNCTION_SIGNATURE(glXMakeCurrent) = (fp_glXMakeCurrent*)Linux_GetGLFunction("glXMakeCurrent");
FUNCTION_SIGNATURE(glXGetFBConfigAttrib) = (fp_glXGetFBConfigAttrib*)Linux_GetGLFunction("glXGetFBConfigAttrib");
FUNCTION_SIGNATURE(glViewport) = (fp_glViewport*)Linux_GetGLFunction("glViewport");

#include "Linux/Linux_Window.cpp"
#include "Linux/Linux_OpenGL.cpp"
#include "Linux/Linux_LoadSystem.cpp"

#endif
