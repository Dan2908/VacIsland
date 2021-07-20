#ifndef H_VBO
#define H_VBO
#include <iostream>
#include <GL/glew.h>
#include "utility.h"

/** Base Buffer Object class*/
class BufferObject{
    GLenum type;
    int stride;
public:
    unsigned int ID;
    BufferObject(GLenum type, int stride);
    ~BufferObject();
    template<typename T>
    int get_stride();
    void bind();
    void unbind();
protected:
    void bufferData(const void* data, long long size);
};

class VertexBuffer : public BufferObject{
public:
    VertexBuffer(float *vertices, long long size, int stride);
};

class ElementBuffer : public BufferObject{
public:
    ElementBuffer(unsigned int *indices, long long size, int stride);
};

class VertexArrayObject{
public:
    unsigned int ID;
    VertexArrayObject();
    ~VertexArrayObject();
    void setVertexBuffer(VertexBuffer &VBO, int layout);
    void setVertexBuffers(VertexBuffer &VBO, int n, ...);
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