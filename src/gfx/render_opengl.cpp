#include "render_opengl.h"
#include "gl.h"
#include "utils/log.h"

using namespace gfxOpenGL;

void RenderOpenGL::printBasicInfo()
{
    PrintD("%s", glGetString(GL_RENDERER));
    PrintD("%s", glGetString(GL_VERSION));
}

// render a sample
#include "gfx/samples/sphere_obj/sphere_obj.h"
static SphereObj sphere;

void RenderOpenGL::render()
{
    static bool loaded = false;
    if (!loaded) sphere.loadOpenGL(); loaded = true;
    
    // opengl state machine ...
    // glClearColor(0.129f, 0.586f, 0.949f, 1.0f);
    // glClear(GL_COLOR_BUFFER_BIT);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    glUseProgram(sphere.shader);
    glBindVertexArray(sphere.vao);
    glDrawArrays(GL_TRIANGLES, 0, sphere.vertCount);
}