#if !defined(WIN32_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "hid.lib")

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <hidsdi.h>

#define WGL_CONTEXT_MAJOR_VERSION_ARB             0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB             0x2092
#define WGL_CONTEXT_LAYER_PLANE_ARB               0x2093
#define WGL_CONTEXT_FLAGS_ARB                     0x2094
#define WGL_CONTEXT_PROFILE_MASK_ARB              0x9126
#define WGL_CONTEXT_DEBUG_BIT_ARB                 0x0001
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB    0x0002
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB          0x00000001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002
#define ERROR_INVALID_VERSION_ARB                 0x2095
#define ERROR_INVALID_PROFILE_ARB                 0x2096

typedef HGLRC fp_wglCreateContextAttribsARB_(HDC DeviceContext, HGLRC ShareContext,
                                            const int *AttribList);
FUNCTION_SIGNATURE(wglCreateContextAttribsARB_);
#define wglCreateContextAttribsARB wglCreateContextAttribsARB_ 

typedef PROC fp_wglGetProcAddress_(LPCSTR lpszProc);
FUNCTION_SIGNATURE(wglGetProcAddress_);
#define wglGetProcAddress wglGetProcAddress_

typedef HGLRC fp_wglCreateContext_(HDC hdc);
FUNCTION_SIGNATURE(wglCreateContext_);
#define wglCreateContext wglCreateContext_

typedef BOOL fp_wglDeleteContext_(HGLRC hglrc);
FUNCTION_SIGNATURE(wglDeleteContext_);
#define wglDeleteContext wglDeleteContext_

typedef BOOL fp_wglMakeCurrent_(HDC hdc, HGLRC hglrc);
FUNCTION_SIGNATURE(wglMakeCurrent_);
#define wglMakeCurrent wglMakeCurrent_

#define WIN32_H
#endif
