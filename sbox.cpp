#include <iostream>
#include <fstream>

#define LOG(...) std::cerr << __VA_ARGS__ << std::endl

const float triangle[] = {
        //#positions            #Colors
         0.0f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f, // top
        -0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f, //bottom left
         0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f
    };

template<typename T>
void print_values(T *array, int size, int stride){
    for(int i = 0; i < size; i += stride){
        for(int j = 0; j < stride - 1; j++){
            printf("%.1lf,\t", array[i + j]);
        }
        printf("%.1lf;\n", array[i + stride - 1 ]);
    }
}

const char *path = "triangle.dat";

int main(){

    FILE *f = fopen(path, "wb+");
    long lSize = sizeof(triangle);
    
    fwrite(triangle, lSize, 1, f);

    fclose(f);
    float t[18];
    //reopen
    f = fopen(path, "rb");

    fread(t, lSize, 1, f);

    print_values(t, 18, 6);

    fclose(f);
    return EXIT_SUCCESS;
}