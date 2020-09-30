#include "render_opengl.h"
#include "open_gl.h"
#include "utils/log.h"

using namespace gfxOpenGL;

void RenderOpenGL::printBasicInfo()
{
    gfxLog::info("version: {0} renderer: {1}", glGetString(GL_VERSION), glGetString(GL_RENDERER));
}

// render a sample
#include "gfx/samples/basic_triangle/basic_triangle.h"
static BasicTriangle basicTriangle;

void RenderOpenGL::render()
{
    // glClearColor(0.129f, 0.586f, 0.949f, 1.0f); // rgb(33,150,243)
    // glClear(GL_COLOR_BUFFER_BIT);

    // opengl state machine ...
    static bool loaded = false;
    if (!loaded) basicTriangle.loadOpenGL(); loaded = true;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(basicTriangle.shader);   
    glBindVertexArray(basicTriangle.vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}