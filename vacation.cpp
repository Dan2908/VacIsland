#define LOG(...) std::cerr << __VA_ARGS__ << std::endl
#define VEC_AXIS(x) float(x == X_AXIS), float(x == Y_AXIS), float(x == Z_AXIS)

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
            *   fShader_path = "shader/fragment.glsl",
            *   texture_path = "res/img/wall.jpg";
static bool     wireframe    = false;
static float    zoom         = 1.0f,
                camX         = 0.0f;
glm::vec3       camPos(0.0f, 0.0f, zoom), 
                camTarget(0.0f, 0.0f, 0.0f),
                camUp(0.0f, 1.0f, 0.0f); 

enum AXIS{
    X_AXIS = 10,
    Y_AXIS, 
    Z_AXIS
};

//  -------------------------------- DECLARATIONS --------------------------------   //

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
/* Entrada de teclado */
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void processInput(GLFWwindow *window);

void rotate_model(glm::mat4 &model, float radians, AXIS axis);

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
    glfwSetScrollCallback(window, scroll_callback);

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

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.5f,  0.5f, 0.0f), 
        glm::vec3( 0.5f, -0.5f, 0.0f),
        glm::vec3(-0.5f,  0.5f, 0.0f),  
        glm::vec3(-0.5f, -0.5f, 0.0f) 
    };

    ShaderProgram program(vShader_path, fShader_path);
    VertexArrayObject VAO;
    VertexBuffer VBO(vertices, sizeof(vertices), 3);
    VertexBuffer Triangle(triangle, sizeof(triangle), 6);
    VertexBuffer Cube("res/asset/cube.dat", 180 * sizeof(float), 5);
    ElementBuffer EBO(indices, sizeof(indices), 3);

    //VAO.setVertexBuffer(VBO, 0);
    VAO.setVertexBuffers(VBO, 1, 3);
    VAO.enableAttribptr(0);
    EBO.bind();
    //Matrixes
    

    program.use();
    //Texture texture(texture_path); 

    while(!glfwWindowShouldClose(window)){
    // input
    // rendering
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, zoom));
        
        //view = glm::lookAt(camPos, camTarget, camUp);


        program.setMat4("model", glm::value_ptr(model));
        program.setMat4("view", glm::value_ptr(view));
        program.setMat4("projection", glm::value_ptr(projection));

        int cols = 10, rows = 10;
        float size = 0.5f;
        float middle = cols * size / 2;

        float x_off = -middle;
        while(x_off < middle){
            program.setFloat("x_offset", x_off);
            float y_off = -middle;
            while(y_off < middle){
                program.setFloat("y_offset", y_off);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                y_off += size;
            }
            x_off += size;
        }

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

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    zoom += yoffset;
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