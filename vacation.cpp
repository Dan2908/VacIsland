#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define LOG(...) std::cerr << __VA_ARGS__ << std::endl
const int WIDTH = 800, HEIGHT = 600;
const char *vsSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main(){\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}"
    ;
const char *fsSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main(){\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n"
    ;

/* Función para informar a OpenGL los cambios de dimensión y ubicación de la ventana.
    Llama a glViewport() */
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
/* Entrada de teclado */
void processInput(GLFWwindow *window);
/* Verifica si la compilación del shader fue exitosa. Mustra error si no.*/
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
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
// Vertex Buffer Object VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    /* Shaders */
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vertexShader, 1, &vsSource, NULL);
    glShaderSource(fragmentShader, 1, &fsSource, NULL);

    glCompileShader(vertexShader);
    if(!shader_compiled(vertexShader)) 
        return EXIT_FAILURE;
    glCompileShader(fragmentShader);
    if(!shader_compiled(fragmentShader)) 
        return EXIT_FAILURE;
    /* Program */
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    
    glLinkProgram(shaderProgram);
    if(!program_linked(shaderProgram)) 
        return EXIT_FAILURE;
    /* Deattach*/
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glUseProgram(shaderProgram);

    while(!glfwWindowShouldClose(window)){
    // input
        processInput(window);
    // rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    // events and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height){
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}