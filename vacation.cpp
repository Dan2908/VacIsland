#include <iostream>
#include <GLFW/glfw3.h>



int main(){
    if(!glfwInit()){
        perror("Error al iniciar glfw");
        return -1;
    }

    perror("FIN");
    return EXIT_SUCCESS;
}