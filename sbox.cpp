#include <iostream>

#define LOG(...) std::cerr << __VA_ARGS__ << std::endl

#include "base/shapes.h"

typedef float position[3];

int main(){
    Rectangle R;

    float vertices[4 * s_stride];
    R.vertex_buffer(vertices);

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < s_stride; j++){
            std::cout << vertices[i*s_stride +j]<< " ";
        }
        std::cout << std::endl;
    }


    return EXIT_SUCCESS;
}

/*

0 0 0 0 0 0 0 0
1 0 0 0 0 0 0 0
0 1 0 0 0 0 0 0
1 1 0 0 0 0 0 0
* * * * *
* * * * *
* 2 * * *
* 0 1 * *
* * * * *

*/