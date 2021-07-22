#include <iostream>
#include <fstream>

#define LOG(...) std::cerr << __VA_ARGS__ << std::endl

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

const float triangle[] = {
        //#positions            #Colors
         0.0f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f, // top
        -0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f, //bottom left
         0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f
    };

const size_t get_file_size(FILE *f) {
    fseek(f, 0, SEEK_END);
    size_t output = ftell(f);
    rewind(f);
    return output;
}

FILE *safe_fopen(const char* path, const char* mode){
    FILE *f = fopen(path, mode);
    if(f == NULL)
        perror("File Error.");
    return f;
}

const int safe_fclose(FILE *file){
    int ret = ferror(file);
    fclose(file);
    return ret;
}

template<typename T>
void print_values(T *array, int size, int stride){
    for(int i = 0; i < size; i += stride){
        for(int j = 0; j < stride - 1; j++){
            printf("%.1lf,\t", array[i + j]);
        }
        printf("%.1lf;\n", array[i + stride - 1 ]);
    }
}

template<typename T>
int save_data(const char *file_path, T &data, size_t size){
    FILE *f = safe_fopen(file_path, "wb+");
    
    fwrite(data, size, 1, f);

    return safe_fclose(f);
}
template<typename T>
T* read_data(const char *file_path){
    FILE *f = safe_fopen(file_path, "rb");
    size_t size = get_file_size(f);
    
    T* res = (T*)malloc(size);
    fread(res, size, 1, f);

    safe_fclose(f); 
    return res;
}

const char *path = "res/asset/cube.dat";

int main(){

    float *cube = read_data<float>("res/asset/cube.dat");
    LOG(sizeof(cube));

    return EXIT_SUCCESS;
}