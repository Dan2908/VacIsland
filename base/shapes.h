#ifndef SHAPES_H
#define SHAPES_H

#include <cstdlib>
#include "utility.h"
#include "geometry.h"
#include "glFunc.h"

static unsigned int PROPORTION = 1000;
static unsigned int DEFAULT_SIZE = 1000;

template<typename T, typename U>
T normalize(U x){ return (T)(x/PROPORTION); }

class Shape{
    Point origin;
public:
    Shape(Point p);
    Shape(int x = 0, int y = 0);
    float *get_normals(float *dest);
};

class Rect : Shape{
    Point v1;
public:
    Rect(Point v1);
    Rect(Point v0, Point v1);
};

class Triangle : Shape{
    Point v1, v2;
public:
    Triangle();
    Triangle(Point v1, Point v2, Point v0 = 0);
};

class Rectangle : Shape{
    Point v1, v2, v3;
public:
    Rectangle();
    float *vertex_buffer_array(float *destArray);
    VertexBuffer vertex_buffer();
    ElementBuffer element_buffer(bool inverse);
};

#endif