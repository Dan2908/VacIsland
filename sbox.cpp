#include <iostream>

#define LOG(...) std::cerr << __VA_ARGS__ << std::endl

#include "base/shapes.h"

typedef float position[3];

int main(){
    int W = 5, H = 5;
    Surface S(W, H, 200);

    shapes::vArray vb(S);
    float *vBuffer = vb.get_array();

    for(int i = W; i >= 0; i--){
        for(int j = 0; j <= H; j++){
            float * p = vb.get_vertex_data(j*(H+1) + i);
            printf("(%f, %f)\t", p[X],  p[Y]);
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