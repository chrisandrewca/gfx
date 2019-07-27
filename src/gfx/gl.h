#ifndef _GFX_WIN_GL_
#define _GFX_WIN_GL_

#include <opengl/khr/khrplatform.h>
#include <opengl/glcorearb.h>
#include <opengl/wglext.h>

namespace gfxOpenGL
{
void *GetAnyGLFuncAddress(const char *name);
extern PFNGLGETSTRINGPROC glGetString;
extern PFNGLCLEARCOLORPROC glClearColor;
extern PFNGLCLEARPROC glClear;

void InitializeContextDependantFunctions();
extern PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
extern PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
} // namespace gfxOpenGL

#endif