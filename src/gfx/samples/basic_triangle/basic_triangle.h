#ifndef _GFX_BASIC_TRIANGLE_
#define _GFX_BASIC_TRIANGLE_

#include "gfx/gl.h"

class BasicTriangle
{
public:
    /*
     * OpenGL
     */
    GLuint vao = 0;
    GLuint shader = 0;

    void loadOpenGL()
    {
        float vertices[9] = {
            0.0f, 0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f};
        float colors[9] = {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f};

        const char *vertexShader =
            "#version 400\n"
            "layout(location = 0) in vec3 vp;"
            "layout(location = 1) in vec3 vc;"
            "out vec3 color;"
            "void main(){color=vc;gl_Position = vec4(vp, 1.0);}";
        const char *fragShader =
            "#version 400\n"
            "in vec3 color;"
            "out vec4 fc;"
            "void main(){fc = vec4(color, 1.0);}";

        // opengl state machine ...
        GLuint vertsVbo = 0;
        glGenBuffers(1, &vertsVbo);
        glBindBuffer(GL_ARRAY_BUFFER, vertsVbo);
        glBufferData(GL_ARRAY_BUFFER,
                     9 * sizeof(float),
                     vertices,
                     GL_STATIC_DRAW);

        GLuint colorsVbo = 0;
        glGenBuffers(1, &colorsVbo);
        glBindBuffer(GL_ARRAY_BUFFER, colorsVbo);
        glBufferData(GL_ARRAY_BUFFER,
                     9 * sizeof(float),
                     colors,
                     GL_STATIC_DRAW);

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vertsVbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glBindBuffer(GL_ARRAY_BUFFER, colorsVbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        // TODO learn how to organize shaders ...
        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &vertexShader, nullptr);
        glCompileShader(vs); // TODO learn error handling

        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &fragShader, nullptr);
        glCompileShader(fs);

        shader = glCreateProgram();
        ValidateShader(shader);
        PrintShaderDetails(shader);

        glAttachShader(shader, vs);
        glAttachShader(shader, fs);
        glLinkProgram(shader);
    }

    // ...
};

#endif