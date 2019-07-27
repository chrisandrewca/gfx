#include "render_opengl.h"
#include "gl.h"

using namespace gfxOpenGL;

void RenderOpenGL::render()
{
    //glClearColor(0.129f, 0.586f, 0.949f, 1.0f); // rgb(33,150,243)
    glClearColor(1.0f, 0, 0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}