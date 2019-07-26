#ifndef _GFX_WIN_GL_
#define _GFX_WIN_GL_

#include <opengl/khr/khrplatform.h>
#include <opengl/glcorearb.h>
#include <opengl/wglext.h>

namespace gfxWingl
{
template <class T>
T GetAnyGLFuncAddress(const char *name)
{
    void *p = (void *)wglGetProcAddress(name);
    if (p == 0 ||
        (p == (void *)0x1) || (p == (void *)0x2) || (p == (void *)0x3) ||
        (p == (void *)-1))
    {
        HMODULE module = LoadLibraryA("opengl32.dll");
        p = (void *)GetProcAddress(module, name);
    }

    return reinterpret_cast<T>(p);
}

static auto glGetString = GetAnyGLFuncAddress<PFNGLGETSTRINGPROC>("glGetString");
static auto glClearColor = GetAnyGLFuncAddress<PFNGLCLEARCOLORPROC>("glClearColor");
static auto glClear = GetAnyGLFuncAddress<PFNGLCLEARPROC>("glClear");

} // namespace gfxWingl

#endif