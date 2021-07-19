#include <iostream>

#define LOG(...) std::cerr << __VA_ARGS__ << std::endl

const char *vs_path = "shader/vertex.glsl",
           *fs_path = "shader/fragment.glsl";

int main(){
    FILE *f = fopen(vs_path, "r");
    long lSize;
    char *str;

    //File size
    fseek(f, 0, SEEK_END);
    lSize = ftell(f);
    rewind(f);

    str = (char*)malloc(sizeof(char)*lSize);
    if(str == NULL) LOG("Memory allocation failure");

    fread(str, lSize, 1, f);

    for(int i = 0; str[i] != '\0'; i++){
        printf("%c", str[i]);
    }

    fclose(f);
    return EXIT_SUCCESS;
}