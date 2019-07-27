#include "gl.h"

namespace gfxOpenGL
{
PFNGLGETSTRINGPROC glGetString = (PFNGLGETSTRINGPROC)GetAnyGLFuncAddress("glGetString");
PFNGLCLEARCOLORPROC glClearColor = (PFNGLCLEARCOLORPROC)GetAnyGLFuncAddress("glClearColor");
PFNGLCLEARPROC glClear = (PFNGLCLEARPROC)GetAnyGLFuncAddress("glClear");
} // namespace gfxOpenGL