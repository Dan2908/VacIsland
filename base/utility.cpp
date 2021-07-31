#ifndef LOG
#define LOG(...) std::cerr << __VA_ARGS__ << std::endl
#endif

#include "utility.h"

char* util::read_file(const char *fileName){
    FILE *f;
    long lSize;
    char* str;

    f = safe_fopen(fileName, "rb"); // Open file
    if(f == NULL) { return NULL; }  // Check error

    lSize = get_file_size(f) + 1;                 //Get file size
    str = (char*)malloc(sizeof(char)*lSize);  // Allocate string
    size_t result = fread(str, lSize, 1, f);  // Read file
    
    if(result != lSize && !feof(f))         // Check errors
        LOG("File read failure!\nsize: " << lSize);          //

    str[lSize - 1] = '\0';      // Close string
    safe_fclose(f);
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
        perror("Error opening file.");
    return stream;
}

const int util::safe_fclose(FILE *stream){
    int ret = ferror(stream);
    fclose(stream);
    return ret;
}
