#ifndef SHAPES_H
#define SHAPES_H

#include "utility.h"
#include "geometry.h"

static const unsigned int   s_ratio = 1000,
                            s_vertices = 3,
                            s_color = 3,
                            s_texture = 2,
                            s_stride = s_vertices + s_color + s_texture;

typedef int     VertexDatai[s_stride];
typedef float   VertexDataf[s_stride];

float normalize(float n);

class Shape{
protected:
    int  n_vertices,
        *vertex_data;
public:
    Shape(const int n_vertices);
    void set_pos(Point pos, int dest_vertex);
    void set_color(Point color, int dest_vertex);
    void set_texture(Point tex_coord, int dest_vertex);
    size_t vertex_buffer_size();
    long long element_buffer_size();
};

class Rectangle : public Shape{
    float *vertex_buffer(float *dest);
    unsigned int *element_buffer(bool reverse_order, unsigned int *dest);
public:
    Rectangle();
    Rectangle(int size_square);
    Rectangle(int w, int h);
    Rectangle(int w, int h, Point offset);
    void get_buffer_data(float *vertex_array, unsigned int *element_array, bool reverse_order);
};

#endif