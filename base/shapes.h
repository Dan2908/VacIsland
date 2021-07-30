#ifndef SHAPES_H
#define SHAPES_H

#include <cstdlib>
#include <stdarg.h>
#include "utility.h"
#include "geometry.h"

static const unsigned int   PROPORTION = 1000,
                            DEFAULT_SIZE = 1000,
                            s_vertices = 3,
                            s_color = 3,
                            s_texture = 2,
                            s_stride = s_vertices + s_color + s_texture;

typedef int     VertexDatai[s_stride];
typedef float   VertexDataf[s_stride];
 

float *get_normals(float *dest, Point p);
float *get_normals(float *dest, int n ...);

class Shape{
protected:
    int n_vertices;
    VertexDatai *vertex_data;
public:
    Shape();
    float *get_vertex_array(VertexDataf dest);
};

class Rect : Shape{
    VertexDatai v1;
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
    float *vertex_buffer(float *dest);
    int *element_buffer();
};

#endif