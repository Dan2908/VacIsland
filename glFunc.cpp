#include <iostream>
#include <GL/glew.h>
#include <stdarg.h>


#define STB_IMAGE_IMPLEMENTATION
#include "glFunc.h"
#include "3rd_party/stb_image.h"
#include "utility.h"

BufferObject::BufferObject(unsigned int type, int stride) : type(type), stride(stride) 
                                                     { glGenBuffers(1, &ID); }
BufferObject::~BufferObject()                        { glDeleteBuffers(1, &ID); }         
void BufferObject::bind()                            { glBindBuffer(type, ID); }
void BufferObject::unbind()                          { glBindBuffer(type, 0); }
void BufferObject::bufferData(const void* data, long long size)
{
    bind();
    glBufferData(type, size, data, GL_STATIC_DRAW);
    unbind();
}
int BufferObject::get_stride()  { return stride; }


//  Vertex Buffer
VertexBuffer::VertexBuffer(float *vertices, long long size, int stride) : BufferObject(GL_ARRAY_BUFFER, stride){
    bufferData(vertices, size);
}
VertexBuffer::VertexBuffer(const char *file_path, long long size, int stride) : BufferObject(GL_ARRAY_BUFFER, stride){
    float *data = util::read_data<float>(file_path);
    bufferData(data, size);
    free(data);
}

//  Element Buffer
ElementBuffer::ElementBuffer(unsigned int *indices, long long size, int stride) : BufferObject(GL_ELEMENT_ARRAY_BUFFER, stride){
    bufferData(indices, size);
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
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, VBO.get_stride() * sizeof(float), (void*)0);
    VBO.unbind();
    unbind();
}
void VertexArrayObject::setVertexBuffers(VertexBuffer &VBO, int n, ...)
{
    bind();
    VBO.bind();
    va_list vl;
    va_start(vl, n);
    int offset = 0, size;
    for(int layout = 0; layout < n; layout++){
        size = va_arg(vl, int);
        glVertexAttribPointer(layout, size, GL_FLOAT, GL_FALSE, VBO.get_stride() * sizeof(float), (void*)(offset * sizeof(float)));
        offset += size;
    }
    va_end(vl);
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

/* =======================\\
 * \\   TEXTURE            \\
 *  \\======================*/

Texture::Texture(const char *img_path)
{ 
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int w, h, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(img_path, &w, &h, &nrChannels, 0);
    if(data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        std::cerr << "failed to load texture..." << std::endl;
    }
    stbi_image_free(data);
}

Texture::~Texture(){}

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
    char *src = util::read_file(path);
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

void ShaderProgram::setMat4(const char *sName, const float *data){
    glUniformMatrix4fv(glGetUniformLocation(ID, sName), 1, GL_FALSE, data);
}

void ShaderProgram::setVec3(const char *sName, const float *data){
    glUniform3fv(glGetUniformLocation(ID, sName), 1, data);
}

void ShaderProgram::setFloat(const char *sName, const float data){
    glUniform1f(glGetUniformLocation(ID, sName), data);
}

