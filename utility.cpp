#ifndef LOG
#define LOG(...) std::cerr << __VA_ARGS__ << std::endl
#endif

#include <iostream>
#include "utility.h"

char *read_file(const char *fileName){
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