#ifndef _GFX_SPHERE_OBJ_
#define _GFX_SPHERE_OBJ_

#include "utils/log.h"

#include <tinyobjloader/tiny_obj_loader.h>
#include <vector>

class SphereObj
{
public:
    /*
     * OpenGL
     */
    GLuint vao = 0;
    GLuint shader = 0;
    int vertCount = 0;

    void loadOpenGL()
    {
        const char *vertexShader =
            "#version 400\n"
            "layout(location = 0) in vec3 vp;"
            "void main(){gl_Position = vec4(vp, 1.0);}";
        const char *fragShader =
            "#version 400\n"
            "out vec4 fc;"
            "void main(){fc = vec4(0.5, 0, 0.5, 1.0);}";

        tinyobj::attrib_t attrib;
        loadModel(attrib);
        vertCount = attrib.vertices.size();

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        GLuint vertsVbo = 0;
        glGenBuffers(1, &vertsVbo);
        glBindBuffer(GL_ARRAY_BUFFER, vertsVbo);
        glBufferData(GL_ARRAY_BUFFER,
                     vertCount * sizeof(float),
                     attrib.vertices.data(),
                     GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(0);

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

protected:
    bool loadModel(tinyobj::attrib_t &attrib)
    {
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> mats;

        std::string warn;
        std::string err;

        // this filepath depends on the working directory
        // TODO somehow set working directory in some type of single global place...
        auto loaded = tinyobj::LoadObj(&attrib, &shapes, &mats, &warn, &err,
                                       "src/gfx/samples/sphere_obj/sphere.obj",
                                       "src/gfx/samples/sphere_obj/",
                                       true);

        if (!warn.empty())
            PrintD("%s", warn.c_str());
        if (!err.empty())
            PrintD("%s", err.c_str());

        return loaded;
    }
};

#endif