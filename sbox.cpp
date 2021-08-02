#include <iostream>

#define LOG(...) std::cerr << __VA_ARGS__ << std::endl

#include "base/shapes.h"

typedef float position[3];

int main(){
    int W = 5, H = 5;
    Surface S(W, H, 200);
    int *vdata = S.get_vertex_data();

    for(int i = W; i >= 0; i--){
        for(int j = 0; j <= H; j++){
            printf("(%i, %i)\t", vdata[i*s_stride + j*(H+1)*s_stride], vdata[i*s_stride + j*(H+1)*s_stride + 1]);
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