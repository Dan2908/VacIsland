#define LOG(...) std::cerr << __VA_ARGS__ << std::endl

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <memory>

#include "utility.h"
#include "glFunc.h"

const int    WIDTH = 800, 
             HEIGHT = 600;
const char  *vShader_path = "shader/vertex.glsl",
            *fShader_path = "shader/fragment.glsl";
bool wireframe = false;

//  -------------------------------- DECLARATIONS --------------------------------   //

unsigned int get_shader(const char *source, unsigned int type);
unsigned int get_program(const char *vs_src, const char *fs_src);
/* Función para informar a OpenGL los cambios de dimensión y ubicación de la ventana.
    Llama a glViewport() */
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
/* Entrada de teclado */
void processInput(GLFWwindow *window);
/* Verifica si la compilación del shader fue exitosa. Mustra error si no.*/
bool shader_compiled(unsigned shader);
/* Verifica si el enlace en el programa fue exitoso. Mustra error si no.*/
bool program_linked(unsigned program);
//  -------------------------------- APPLICATION --------------------------------   //

int main(){
//Iniciar GLFW
    if(!glfwInit()){
        LOG("Error al iniciar glfw");
        return EXIT_FAILURE;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
// Creación de ventana
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Vacation Island", NULL, NULL);
    if(window == NULL){
        LOG("Error creando ventana");
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(window); // poner en contexto principal

    if(glewInit() != GLEW_OK){
        LOG("Error al iniciar GLEW");
        return EXIT_FAILURE;
    }

    glViewport(0,0,WIDTH, HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
// Dibujar
    float vertices[] = {
        -0.5f,  0.5f, 0.0f, // top left
        -0.5f, -0.5f, 0.0f, // bottom left
         0.5f,  0.5f, 0.0f, // top right
         0.5f, -0.5f, 0.0f  // bottom right
    };
    unsigned int indices[]{
        0, 1, 2,    // triangle 1
        2, 1, 3     // triangle 2
    };
// Vertex Buffer Object VBO
    unsigned int shaderProgram = get_program(vShader_path, fShader_path);
    VBO buffer(vertices, sizeof(vertices));
    EBO eBufer(indices, sizeof(indices));
    VAO vao;
    vao.linkVBO(buffer, 0);


    while(!glfwWindowShouldClose(window)){
    // input
        processInput(window);
    // rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shaderProgram);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    // events and swap buffers
        glfwSwapBuffers(window);
        glfwWaitEvents();
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}

//  -------------------------------- DEFINITIONS --------------------------------   //

void framebuffer_size_callback(GLFWwindow *window, int width, int height){
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        if(wireframe)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        wireframe = !wireframe;
    }

}

unsigned int get_shader(const char *srcPath, GLenum type){
    unsigned int shaderID = glCreateShader(type);
    char *src = read_file(srcPath);
    glShaderSource(shaderID, 1, &src, NULL);
    glCompileShader(shaderID);
    if(!shader_compiled(shaderID))
        LOG( ((type == GL_VERTEX_SHADER) ? "VERTEX " : "FRAGMENT ") << "SHADER ERROR.");
    free(src);
    return shaderID;
}

unsigned int get_program(const char *vs_path, const char *fs_path){
    unsigned int programID             = glCreateProgram(),
                 VertexShader          = get_shader(vs_path, GL_VERTEX_SHADER),
                 FragmentShader        = get_shader(fs_path, GL_FRAGMENT_SHADER);

    glAttachShader(programID, VertexShader);
    glAttachShader(programID, FragmentShader);
    glLinkProgram(programID);

    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);

    return programID;
}

bool shader_compiled(unsigned shader){
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        LOG("Error compilando shader: " << infoLog);
        return false;
    }
    return true;
}
/* Verifica si el enlace en el programa fue exitoso. Mustra error si no.*/
bool program_linked(unsigned program){
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        LOG("Error linking program: " << infoLog);
        return false;
    }
    return true;
}