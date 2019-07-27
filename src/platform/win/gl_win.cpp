#include "gfx/gl.h"

namespace gfxOpenGL
{
void *GetAnyGLFuncAddress(const char *name)
{
    void *p = (void *)wglGetProcAddress(name);
    if (p == 0 ||
        (p == (void *)0x1) || (p == (void *)0x2) || (p == (void *)0x3) ||
        (p == (void *)-1))
    {
        HMODULE module = LoadLibraryA("opengl32.dll");
        p = (void *)GetProcAddress(module, name);
    }

    return p;
}

void InitializeContextDependantFunctions()
{
    wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)GetAnyGLFuncAddress("wglChoosePixelFormatARB");
    wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)GetAnyGLFuncAddress("wglCreateContextAttribsARB");
}

PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = nullptr;
PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;
} // namespace gfxOpenGL