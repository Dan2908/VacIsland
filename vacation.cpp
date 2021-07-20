#define LOG(...) std::cerr << __VA_ARGS__ << std::endl

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>

#include "3rd_party/glm/glm.hpp"
#include "3rd_party/glm/gtc/matrix_transform.hpp"
#include "3rd_party/glm/gtc/type_ptr.hpp"
#include "glFunc.h"

const int       WIDTH = 800, 
                HEIGHT = 600;
const char  *   vShader_path = "shader/vertex.glsl",
            *   fShader_path = "shader/fragment.glsl";
static bool     wireframe    = false;
static float    angle        = 45.0f,
                model_angle  = -55.0f;

float cube[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

//  -------------------------------- DECLARATIONS --------------------------------   //

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
/* Entrada de teclado */
void processInput(GLFWwindow *window);

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
    float triangle[] = {
        //#positions            #Colors
         0.0f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f, // top
        -0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f, //bottom left
         0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f
    };
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

    ShaderProgram program(vShader_path, fShader_path);
    VertexArrayObject VAO;
    VertexBuffer VBO(vertices, sizeof(vertices), 3);
    VertexBuffer Triangle(triangle, sizeof(triangle), 6);
    VertexBuffer Cube(cube, sizeof(cube), 5);
    ElementBuffer EBO(indices, sizeof(indices), 3);

    //VAO.setVertexBuffer(VBO, 0);
    VAO.setVertexBuffers(Cube, 2, 3, 2);
    VAO.enableAttribptr(0);
    VAO.enableAttribptr(1);
   //EBO.bind();
    //Matrixes

    


    program.use();

    while(!glfwWindowShouldClose(window)){
    // input
        processInput(window);
    // rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);;
    
        model = glm::rotate(model, glm::radians(model_angle), glm::vec3(1.0f, 0.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(angle), float(WIDTH) / float(HEIGHT), 0.1f, 100.0f); 
        
        program.setMat4("model", glm::value_ptr(model));
        program.setMat4("view", glm::value_ptr(view));
        program.setMat4("projection", glm::value_ptr(projection));
        /*
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::rotate(transform, float(glfwGetTime()) , glm::vec3(0.0, 0.0, 1.0));
        transform = glm::translate(transform, glm::vec3(0.5, -0.5, 0.5));
    
        glUniformMatrix4fv(glGetUniformLocation(program.ID, "transMatrix"), 1, GL_FALSE, glm::value_ptr(transform));
        float time = glfwGetTime();
        float greenValue    = (sin(time/2.0f) / 2.0f) + 0.5f;
        float redValue      = (cos(time/2.0f) / 2.0f) + 0.5f;
        float blueValue      = (sin(time) / 2.0f) + 0.5f;
        glUniform4f(vertexColorLocation, redValue, greenValue, blueValue, 1.0f);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        */
        glDrawArrays(GL_TRIANGLES, 0, 36);
    // events and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
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
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        angle += 0.01f;
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        angle -= 0.01f;
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        model_angle += 0.01f;
    }
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        model_angle -= 0.01f;
    }
}