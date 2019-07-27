#ifndef _GFX_BASIC_TRIANGLE_
#define _GFX_BASIC_TRIANGLE_

#include "gfx/gl.h"

class BasicTriangle
{
public:
    int vertCount = 9;
    float vertices[9] = {
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f};

    // OpenGL
    GLuint vao = 0;
    GLuint shader = 0;

    void loadOpenGL()
    {
        const char *vertexShader =
            "#version 400\n"
            "in vec3 vp;"
            "void main(){gl_Position = vec4(vp, 1.0);}";
        const char *fragShader =
            "#version 400\n"
            "out vec4 color;"
            "void main(){color = vec4(0.129, 0.586, 0.949, 1.0);}";

        // load the basic triangle sample
        GLuint vbo = 0;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER,
                     vertCount * sizeof(float),
                     vertices,
                     GL_STATIC_DRAW);

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glEnableVertexAttribArray(0);       // enable buffer at position 0 for subsequent calls
        glBindBuffer(GL_ARRAY_BUFFER, vbo); // bind VBO above to VAO @ pos.0
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        // TODO learn how to organize shaders ...
        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &vertexShader, nullptr);
        glCompileShader(vs); // TODO learn error handling

        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &fragShader, nullptr);
        glCompileShader(fs);

        shader = glCreateProgram();
        glAttachShader(shader, vs);
        glAttachShader(shader, fs);
        glLinkProgram(shader);
    }

    // ...
};

#endif