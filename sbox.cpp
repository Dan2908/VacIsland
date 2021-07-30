#include <iostream>

#define LOG(...) std::cerr << __VA_ARGS__ << std::endl


typedef float position[3];

int main(){
    position ps;
    ps[0] = 3.1f;
    ps[1] = 2;
    ps[2] = 1;

    LOG(ps[0]);
    LOG(ps[1]);
    LOG(ps[3]);

    return EXIT_SUCCESS;
}

/*
* * * * *
* * * * *
* 2 * * *
* 0 1 * *
* * * * *

*/