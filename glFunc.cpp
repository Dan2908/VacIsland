#include "glFunc.h"

// ##   Vertex Buffer Object.
// ##
VBO::VBO(float *vertices, long long size){
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}
VBO::~VBO()         { glDeleteBuffers(1, &ID); }
void VBO::bind()    { glBindBuffer(GL_ARRAY_BUFFER, ID); }
void VBO::unbind()  { glBindBuffer(GL_ARRAY_BUFFER, 0); }
// ##
// ##   Element Buffer Object.
// ##
EBO::EBO(unsigned int *indices, long long size){
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    unbind();
}
EBO::~EBO()         { glDeleteBuffers(1, &ID); }
void EBO::bind()    { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID); }
void EBO::unbind()  { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
// ##
// ##   Vertex Array Object.
// ##
VAO::VAO()          { glGenVertexArrays(1, &ID); }
VAO::~VAO()         { glDeleteVertexArrays(1, &ID); }
void VAO::bind()    { glBindVertexArray(ID); }
void VAO::unbind()  { glBindVertexArray(0); }
void VAO::linkVBO(VBO VBO, int layout){
    VBO.bind();
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(layout);
    VBO.unbind();
}
