#include <iostream>
#include <fstream>


#define LOG(...) std::cerr << __VA_ARGS__ << std::endl

#include "utility.h"

enum DATA_PTR : int {
    NONE = -1,
    POS_X, POS_Y, POS_Z,    // Positions
    COL_X, COL_Y, COL_Z,    // Colors
    TEX_X, TEX_Y,           // Texture
    ARRAY_SIZE              // Array size
};

struct Vertice{
    float data[ARRAY_SIZE];
    Vertice()
    {   // zero-fill
        for(int i = 0; i < ARRAY_SIZE; i++) { data[i] = 0.0f; }
    }
    Vertice(float x, float y, float z)  :   Vertice()
    {   
        set_position(x, y, z);
    }
    void set_position(float x, float y, float z){
        data[POS_X] = x;
        data[POS_Y] = y;
        data[POS_Z] = z;
    }
    Vertice& operator+=(Vertice& other){
        data[POS_X] += other.data[POS_X];
        data[POS_Y] += other.data[POS_Y];
        data[POS_Z] += other.data[POS_Z];
        return *this;
    } 
};

Vertice operator-(Vertice& one, Vertice& other){
    return Vertice( 
        one.data[POS_X] + other.data[POS_X], 
        one.data[POS_Y] + other.data[POS_Y], 
        one.data[POS_Z] + other.data[POS_Z]);
}

/** Triangle */
struct Triangle{
    Vertice vertices[3];
    float A_size, B_size;
    Triangle() 
    {
        vertices[0] = Vertice(0.0f, 0.0f, 0.0f);    // 90°C vertice
        vertices[1] = Vertice(1.0f, 0.0f, 0.0f);    // Right vertice
        vertices[2] = Vertice(0.0f, 1.0f, 0.0f);    // Top vertice
    }
    /* 90° triangle with origin vertice in {0,0,0}
     * x_vert and y_vert are cordinates for vertices {x, 0, 0} and {0, y, 0} 
     * respectively.
     */
    Triangle(float x_vert, float y_vert) 
    {
        vertices[0] = Vertice(0.0f, 0.0f, 0.0f);            // 90°C vertice
        vertices[1] = Vertice(x_vert, 0.0f, 0.0f);    // Right vertice
        vertices[2] = Vertice(0.0f, y_vert, 0.0f);    // Top vertice
    }
    /* Move triangle to the given position
     * You are moving the first vertice to the position, while
     * other vertices will move respecting the shape.
     */
    void move(Vertice position){
        Vertice offset = vertices[0] - position;
        vertices[0] = position,
        vertices[1] += offset;
        vertices[2] += offset;
    }
};
/*
class Rectangle{
    Triangle triangles[2]; 
    
public:
    Rectangle(){
        triangles[0] = Triangle(1.0f, -1.0f);   //TOP Triangle
        triangles[1] = Triangle(-1.0f, 1.0f);   //Bottom Triangle
        
        triangles[0].move(Vertice(-1.0f, 1.0f, 0.0f));
        triangles[1].move(Vertice(1.0f, -1.0f, 0.0f));
    }
};
*/
const char *path = "res/asset/cube.dat";



int main(){
    float *from = util::read_data<float>(path);
    float to[20];

    unsigned long long size = sizeof(float);

    util::copy_duff_device(from, to, 20);

    for(int i = 0; i < 20; i ++){
        LOG(to[i]);
    }



    return EXIT_SUCCESS;
}

/*
* * * * *
* * * * *
* 2 * * *
* 0 1 * *
* * * * *

*/