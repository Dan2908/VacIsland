#ifndef H_VBO
#define H_VBO
#include <GL/glew.h>

/** Vertex Buffer Object. */
class VBO{
public:
    unsigned int ID;
    VBO(float *vertices, long long size);
    ~VBO();
    void bind();
    void unbind();
};

/** Element Buffer Object*/
class EBO{
public:
    unsigned int ID;
    EBO(unsigned int *indices, long long size);
    ~EBO();
    void bind();
    void unbind();
    void del();};
/** Vertex Array Object */
class VAO{
public:
    unsigned int ID;
    VAO();
    ~VAO();
    void linkVBO(VBO VBO, int layout);
    void bind();
    void unbind();
};

#endif