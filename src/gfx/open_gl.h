#ifndef _GFX_WIN_GL_
#define _GFX_WIN_GL_

#include "utils/debug.h"
#include "utils/log.h"

#include <opengl/khr/khrplatform.h>
#include <opengl/glcorearb.h>
#include <opengl/wglext.h>

namespace gfxOpenGL
{

/*
 * Function Loaders
 * Function loaders must be called for each thread and context ...
 */
void *GetAnyGLFuncAddress(const char *name);

void InitializeContextDependantFunctions();
extern PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
extern PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;

void InitializeOpenGLFunctions();
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLBINDBUFFERPROC glBindBuffer;
extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
extern PFNGLBUFFERDATAPROC glBufferData;
extern PFNGLCLEARCOLORPROC glClearColor;
extern PFNGLCLEARPROC glClear;
extern PFNGLCOMPILESHADERPROC glCompileShader;
extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLCREATESHADERPROC glCreateShader;
extern PFNGLDRAWARRAYSPROC glDrawArrays;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
extern PFNGLGENBUFFERSPROC glGenBuffers;
extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
extern PFNGLGETACTIVEATTRIBPROC glGetActiveAttrib;
extern PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform;
extern PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
extern PFNGLGETSHADERIVPROC glGetShaderiv;
extern PFNGLGETSTRINGPROC glGetString;
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
extern PFNGLLINKPROGRAMPROC glLinkProgram;
extern PFNGLSHADERSOURCEPROC glShaderSource;
extern PFNGLUSEPROGRAMPROC glUseProgram;
extern PFNGLVALIDATEPROGRAMPROC glValidateProgram;
extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;

/*
 * Shader Debugging
 */

// Validate shaders when compiled with DEBUG defined, otherwise noop ...
#define ValidateShader(shaderId)                                            \
    do                                                                      \
    {                                                                       \
        if (VALIDATE_SHADERS_TEST)                                          \
        {                                                                   \
            glValidateProgram(shaderId);                                    \
            auto params = -1;                                               \
            glGetProgramiv(shaderId, GL_VALIDATE_STATUS, &params);          \
            gfxLog::info("program {0} GL_VALIDATE_STATUS = {1}", shaderId, params); \
            if (GL_TRUE != params)                                          \
            {                                                               \
                PrintShaderInfoLog(shaderId);                               \
            }                                                               \
        }                                                                   \
    } while (0)

void PrintShaderDetails(GLuint shaderId);
void PrintShaderInfoLog(GLuint shaderId);
const char *GLTypeToString(GLenum type);

} // namespace gfxOpenGL

#endif