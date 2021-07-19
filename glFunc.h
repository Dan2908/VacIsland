#ifndef H_VBO
#define H_VBO
#include <iostream>
#include <GL/glew.h>
#include "utility.h"

/** Base Buffer Object class*/
class BufferObject{
    GLenum type;
public:
    unsigned int ID;
    BufferObject(GLenum type);
    ~BufferObject();
    void bind();
    void unbind();
protected:
    void bufferData(long long size, const void* data);
};

class VertexBuffer : public BufferObject{
public:
    VertexBuffer(float *vertices, long long size);
};

class ElementBuffer : public BufferObject{
public:
    ElementBuffer(unsigned int *indices, long long size);
};

class VertexArrayObject{
public:
    unsigned int ID;
    VertexArrayObject();
    ~VertexArrayObject();
    void setVertexBuffer(VertexBuffer &VBO, int layout);
    void enableAttribptr(int layout);
    void disableAttribptr(int layout);
    void bind();
    void unbind();
};

class Shader{
    int compile_status;
    void check_error();
    void compile(const char *path);
public:
    unsigned int ID;
    Shader(unsigned int type, const char* path);
    ~Shader();
};

class ShaderProgram
{
    int link_status;
    void check_error();
    void link_program(Shader &vs, Shader &fs);
public:
    unsigned int ID;
    ShaderProgram(const char *vs_path, const char *fs_path);
    ~ShaderProgram();
    void use();
};

#endif