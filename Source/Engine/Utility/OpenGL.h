#if !defined(OPENGL_H)
/* ========================================================================
   $Creator: Armand Karambasis $
   ======================================================================== */

#define GL_COLOR_BUFFER_BIT               0x00004000

typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef signed char GLbyte;
typedef short GLshort;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned int GLuint;
typedef float GLfloat;
typedef float GLclampf;
typedef void GLvoid;
typedef int GLintptrARB;
typedef int GLsizeiptrARB;
typedef int GLfixed;
typedef int GLclampx;

typedef void fp_glClear(GLbitfield mask);
typedef void fp_glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);

static fp_glClear* glClear;
static fp_glClearColor* glClearColor;

#define OPENGL_H
#endif
