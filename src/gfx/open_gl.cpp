#include "open_gl.h"
#include "utils/log.h"

#include <stdio.h>

namespace gfxOpenGL
{
/*
 * Function Loaders
 * Function loaders must be called for each thread and context ...
 */
void InitializeOpenGLFunctions()
{
    glAttachShader = (PFNGLATTACHSHADERPROC)GetAnyGLFuncAddress("glAttachShader");
    glBindBuffer = (PFNGLBINDBUFFERPROC)GetAnyGLFuncAddress("glBindBuffer");
    glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)GetAnyGLFuncAddress("glBindVertexArray");
    glBufferData = (PFNGLBUFFERDATAPROC)GetAnyGLFuncAddress("glBufferData");
    glClearColor = (PFNGLCLEARCOLORPROC)GetAnyGLFuncAddress("glClearColor");
    glClear = (PFNGLCLEARPROC)GetAnyGLFuncAddress("glClear");
    glCompileShader = (PFNGLCOMPILESHADERPROC)GetAnyGLFuncAddress("glCompileShader");
    glCreateProgram = (PFNGLCREATEPROGRAMPROC)GetAnyGLFuncAddress("glCreateProgram");
    glCreateShader = (PFNGLCREATESHADERPROC)GetAnyGLFuncAddress("glCreateShader");
    glDrawArrays = (PFNGLDRAWARRAYSPROC)GetAnyGLFuncAddress("glDrawArrays");
    glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)GetAnyGLFuncAddress("glEnableVertexAttribArray");
    glGenBuffers = (PFNGLGENBUFFERSPROC)GetAnyGLFuncAddress("glGenBuffers");
    glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)GetAnyGLFuncAddress("glGenVertexArrays");
    glGetActiveAttrib = (PFNGLGETACTIVEATTRIBPROC)GetAnyGLFuncAddress("glGetActiveAttrib");
    glGetActiveUniform = (PFNGLGETACTIVEUNIFORMPROC)GetAnyGLFuncAddress("glGetActiveUniform");
    glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)GetAnyGLFuncAddress("glGetAttribLocation");
    glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)GetAnyGLFuncAddress("glGetProgramInfoLog");
    glGetProgramiv = (PFNGLGETPROGRAMIVPROC)GetAnyGLFuncAddress("glGetProgramiv");
    glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)GetAnyGLFuncAddress("glGetShaderInfoLog");
    glGetShaderiv = (PFNGLGETSHADERIVPROC)GetAnyGLFuncAddress("glGetShaderiv");
    glGetString = (PFNGLGETSTRINGPROC)GetAnyGLFuncAddress("glGetString");
    glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)GetAnyGLFuncAddress("glGetUniformLocation");
    glLinkProgram = (PFNGLLINKPROGRAMPROC)GetAnyGLFuncAddress("glLinkProgram");
    glShaderSource = (PFNGLSHADERSOURCEPROC)GetAnyGLFuncAddress("glShaderSource");
    glUseProgram = (PFNGLUSEPROGRAMPROC)GetAnyGLFuncAddress("glUseProgram");
    glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)GetAnyGLFuncAddress("glValidateProgram");
    glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)GetAnyGLFuncAddress("glVertexAttribPointer");
}

extern PFNGLATTACHSHADERPROC glAttachShader = nullptr;
extern PFNGLBINDBUFFERPROC glBindBuffer = nullptr;
extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray = nullptr;
extern PFNGLBUFFERDATAPROC glBufferData = nullptr;
extern PFNGLCLEARCOLORPROC glClearColor = nullptr;
extern PFNGLCLEARPROC glClear = nullptr;
extern PFNGLCOMPILESHADERPROC glCompileShader = nullptr;
extern PFNGLCREATEPROGRAMPROC glCreateProgram = nullptr;
extern PFNGLCREATESHADERPROC glCreateShader = nullptr;
extern PFNGLDRAWARRAYSPROC glDrawArrays = nullptr;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = nullptr;
extern PFNGLGENBUFFERSPROC glGenBuffers = nullptr;
extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = nullptr;
extern PFNGLGETACTIVEATTRIBPROC glGetActiveAttrib = nullptr;
extern PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform = nullptr;
extern PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation = nullptr;
extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = nullptr;
extern PFNGLGETPROGRAMIVPROC glGetProgramiv = nullptr;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = nullptr;
extern PFNGLGETSHADERIVPROC glGetShaderiv = nullptr;
extern PFNGLGETSTRINGPROC glGetString = nullptr;
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = nullptr;
extern PFNGLLINKPROGRAMPROC glLinkProgram = nullptr;
extern PFNGLSHADERSOURCEPROC glShaderSource = nullptr;
extern PFNGLUSEPROGRAMPROC glUseProgram = nullptr;
extern PFNGLVALIDATEPROGRAMPROC glValidateProgram = nullptr;
extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = nullptr;

/*
 * Shader Debugging
 */
void PrintShaderDetails(GLuint shaderId)
{
    gfxLog::info("\nPrintShaderDetails\n----------------");
    auto params = -1;

    glGetProgramiv(shaderId, GL_LINK_STATUS, &params);
    gfxLog::info("GL_LINK_STATUS = %i", params);

    glGetProgramiv(shaderId, GL_ATTACHED_SHADERS, &params);
    gfxLog::info("GL_ATTACHED_SHADERS = %i", params);

    glGetProgramiv(shaderId, GL_ACTIVE_ATTRIBUTES, &params);
    gfxLog::info("GL_ACTIVE_ATTRIBUTES = %i", params);

    for (auto i = 0; i < params; i++)
    {
        auto max_length = 64;
        auto actual_length = 0;
        auto size = 0;
        char name[64];
        GLenum type;

        glGetActiveAttrib(
            shaderId,
            i,
            max_length,
            &actual_length,
            &size,
            &type,
            name);

        if (size > 1)
        {
            for (auto j = 0; j < size; j++)
            {
                char long_name[64];
                sprintf(long_name, "%s[%i]", name, j);
                auto location = glGetAttribLocation(shaderId, long_name);
                gfxLog::info("  %i) type:%s name:%s location:%i",
                       i, GLTypeToString(type), long_name, location);
            }
        }
        else
        {
            auto location = glGetAttribLocation(shaderId, name);
            gfxLog::info("  %i) type:%s name:%s location:%i",
                   i, GLTypeToString(type), name, location);
        }
    }

    glGetProgramiv(shaderId, GL_ACTIVE_UNIFORMS, &params);
    gfxLog::info("GL_ACTIVE_UNIFORMS = %i", params);
    for (auto i = 0; i < params; i++)
    {
        auto max_length = 64;
        auto actual_length = 0;
        auto size = 0;
        char name[64];
        GLenum type;

        glGetActiveUniform(
            shaderId,
            i,
            max_length,
            &actual_length,
            &size,
            &type,
            name);

        if (size > 1)
        {
            for (auto j = 0; j < size; j++)
            {
                char long_name[64];
                sprintf(long_name, "%s[%i]", name, j);
                auto location = glGetUniformLocation(shaderId, long_name);
                gfxLog::info("  %i) type:%s name:%s location:%i",
                       i, GLTypeToString(type), long_name, location);
            }
        }
        else
        {
            auto location = glGetUniformLocation(shaderId, name);
            gfxLog::info("  %i) type:%s name:%s location:%i",
                   i, GLTypeToString(type), name, location);
        }
    }

    PrintShaderInfoLog(shaderId);
}

void PrintShaderInfoLog(GLuint shaderId)
{
    auto max_length = 2048;
    auto actual_length = 0;
    char program_log[2048];
    glGetProgramInfoLog(shaderId, max_length, &actual_length, program_log);
    gfxLog::info("program info log for GL index %u:\n%s", shaderId, program_log);
}

const char *GLTypeToString(GLenum type)
{
    switch (type)
    {
    case GL_BOOL:
        return "bool";
    case GL_INT:
        return "int";
    case GL_FLOAT:
        return "float";
    case GL_FLOAT_VEC2:
        return "vec2";
    case GL_FLOAT_VEC3:
        return "vec3";
    case GL_FLOAT_VEC4:
        return "vec4";
    case GL_FLOAT_MAT2:
        return "mat2";
    case GL_FLOAT_MAT3:
        return "mat3";
    case GL_FLOAT_MAT4:
        return "mat4";
    case GL_SAMPLER_2D:
        return "sampler2D";
    case GL_SAMPLER_3D:
        return "sampler3D";
    case GL_SAMPLER_CUBE:
        return "samplerCube";
    case GL_SAMPLER_2D_SHADOW:
        return "sampler2DShadow";
    default:
        break;
    }
    return "GLTypeToString_unhandled";
}
} // namespace gfxOpenGL