#include "glFunc.h"

BufferObject::BufferObject(GLenum type) : type(type) { glGenBuffers(1, &ID); }
BufferObject::~BufferObject()                        { glDeleteBuffers(1, &ID); }
void BufferObject::bind()                            { glBindBuffer(type, ID); }
void BufferObject::unbind()                          { glBindBuffer(type, 0); }
void BufferObject::bufferData(long long size, const void* data)
{
    bind();
    glBufferData(type, size, data, GL_STATIC_DRAW);
    unbind();
}

//  Vertex Buffer
VertexBuffer::VertexBuffer(float *vertices, long long size) : BufferObject(GL_ARRAY_BUFFER){
    bufferData(size, vertices);
}
//  Element Buffer
ElementBuffer::ElementBuffer(unsigned int *indices, long long size) : BufferObject(GL_ELEMENT_ARRAY_BUFFER){
    bufferData(size, indices);
}
//  Vertex Array Object.
VertexArrayObject::VertexArrayObject()          { glGenVertexArrays(1, &ID); }
VertexArrayObject::~VertexArrayObject()         { glDeleteVertexArrays(1, &ID); }
void VertexArrayObject::bind()                  { glBindVertexArray(ID); }
void VertexArrayObject::unbind()                { glBindVertexArray(0); }
void VertexArrayObject::setVertexBuffer(VertexBuffer &VBO, int layout)
{
    bind();
    VBO.bind();
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    VBO.unbind();
    unbind();
}
void VertexArrayObject::enableAttribptr(int layout)
{ 
    bind();
    glEnableVertexAttribArray(layout); 
}
void VertexArrayObject::disableAttribptr(int layout)
{ 
    glDisableVertexAttribArray(layout);
    unbind();
}

Shader::Shader(unsigned int type, const char* path) : ID(glCreateShader(type))
{
    compile(path);
    check_error();
}
Shader::~Shader() { glDeleteShader(ID); }
void Shader::check_error(){
    if(compile_status == GL_FALSE){
        char infoLog[512];
        glGetShaderInfoLog(ID, 512, NULL, infoLog);
        std::cerr << infoLog << std::endl;
    }
}
void Shader::compile(const char *path){
    char *src = read_file(path);
    glShaderSource(ID, 1, &src, NULL);
    glCompileShader(ID);
    glGetShaderiv(ID, GL_COMPILE_STATUS, &compile_status);
}

ShaderProgram::ShaderProgram(const char *vs_path, const char *fs_path) : ID(glCreateProgram()) 
{
    Shader  vs(GL_VERTEX_SHADER, vs_path),
            fs(GL_FRAGMENT_SHADER, fs_path);
    link_program(vs, fs);
    check_error();
}
ShaderProgram::~ShaderProgram(){
    glDeleteProgram(ID);
};

void ShaderProgram::link_program(Shader &vs, Shader &fs){
    glAttachShader(ID, vs.ID);
    glAttachShader(ID, fs.ID);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &link_status);
}

void ShaderProgram::check_error(){
    if(link_status == GL_FALSE){
        char infoLog[512];
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cerr << infoLog << std::endl;
    }
}

void ShaderProgram::use(){
    glUseProgram(ID);
}

