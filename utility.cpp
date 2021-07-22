#ifndef LOG
#define LOG(...) std::cerr << __VA_ARGS__ << std::endl
#endif

#include <iostream>
#include "utility.h"



char* util::read_file(const char *fileName){
    FILE *f;
    long lSize;
    char* str;

    // Open file
    f = fopen(fileName, "rb");
    if(f == NULL){
        LOG("Filed to open file: '" << fileName << "'.");
        return NULL;
    }
    //Get file size
    fseek(f, 0, SEEK_END);
    lSize = ftell(f) + 1;
    rewind(f);
    // Allocate string
    str = (char*)malloc(sizeof(char)*lSize);
    if(str == NULL){
        LOG("Memory allocation failure");
        return NULL;
    }
    // Read file
    size_t result = fread(str, lSize, 1, f);
    if(result != lSize && !feof(f))
        LOG("File read failure!");
    str[lSize - 1] = '\0';
    // Terminate
    fclose(f);
    return str;
}

const size_t util::get_file_size(FILE *stream) {
    fseek(stream, 0, SEEK_END);
    size_t output = ftell(stream);
    rewind(stream);
    return output;
}

FILE *util::safe_fopen(const char* file_path, const char* mode){
    FILE *stream = fopen(file_path, mode);
    if(stream == NULL)
        perror("File Error.");
    return stream;
}

const int util::safe_fclose(FILE *stream){
    int ret = ferror(stream);
    fclose(stream);
    return ret;
}

template<typename T>
int util::save_data(const char *file_path, T &data, size_t size){
    FILE *f = safe_fopen(file_path, "wb+");
    
    fwrite(data, size, 1, f);

    return safe_fclose(f);
}

template<typename T>
T*  util::read_data(const char *file_path){
    FILE *f = safe_fopen(file_path, "rb");
    size_t size = get_file_size(f);
    
    T* res = (T*)malloc(size);
    fread(res, size, 1, f);

    safe_fclose(f); 
    return res;
}