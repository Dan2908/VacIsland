#ifndef SHAPES_H
#define SHAPES_H

#include "utility.h"
#include "geometry.h"

static const unsigned int s_ratio = 1000,
                          s_position = 3,
                          s_color = 3,
                          s_texture = 2,
                          s_stride = s_position + s_color + s_texture;

typedef unsigned int VertexDatai[s_stride];
typedef float VertexDataf[s_stride];

namespace shapes
{
    float normalize(float n);
    size_t vertex_buffer_size(Shape *shape);
    size_t element_buffer_size(Shape *shape);

    float *get_vertex_buffer(Shape *shape, float *dest);
    unsigned int *get_element_buffer();
    /**
     * Sets Shape's vertex with the provided data (used internally in specific s)
     * @param dest_array Shape vertex array to modify.
     * @param count size of ints to be copied 
     * @param index array position for the first element to be copied.
     * @param data Point class with the dta to be copied. 
     * @return Pointer to the destination array. 
     */
    unsigned int *set_vdata(VertexDatai *dest_array, int count, int index, Point data);
}

unsigned int *shapes::set_vdata(unsigned int *dest_array, int count, int index, Point data)
{
    memcpy(dest_array + index * s_stride, data.coords, count * sizeof(unsigned int));
    return dest_array;
}

class Shape
{
private:
    /**
     * Sets Shape's vertex with the provided data (used internally in specific s)
     * @param dest_array Shape vertex array to modify.
     * @param count size of ints to be copied 
     * @param index array position for the first element to be copied.
     * @param data Point class with the dta to be copied. 
     * @return Pointer to the destination array. 
     */
    unsigned int *set_vdata(VertexDatai *dest_array, int count, int index, Point data);
protected:
    unsigned int m_vertexCount;
    unsigned int *m_vertices;

public:
    Shape(const int n_vertices);
    ~Shape();
    void set_pos(Point data, int vertex);
    void set_color(Point data, int vertex);
    void set_texture(Point data, int vertex);
};

class Rectangle : virtual public Shape
{
    unsigned int *element_buffer(bool reverse_order, unsigned int *dest);

public:
    Rectangle();
    Rectangle(int square_size);
    Rectangle(int w, int h);
    Rectangle(int w, int h, Point offset);
    void get_buffer_data(float *vertex_array, unsigned int *element_array, bool reverse_order);
};

class Surface : public Shape
{
    unsigned int *element_buffer(int w, int h, unsigned int *dest);

public:
    Surface();
    Surface(int squares_w, int squares_h, int square_size);
    int *get_vertex_data() { return vertex_data; }
};

unsigned int *Surface::element_buffer(int w, int h, unsigned int *dest)
{
    *dest++ = 0;
    *dest++ = 1;
    *dest++ = 4;
    *dest++ = 1;
    *dest++ = 4;
    *dest++ = 5;
}

#endif