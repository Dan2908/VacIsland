#ifndef SHAPES_H
#define SHAPES_H

#define PROPORTION 1000         // Vertex data shall be divided by this to get actual GL float values
#define STRIDE_SIZE_POSCOLTEX   // Vertex data array of 8 elements position(3), color(3), texture(2)

#ifdef STRIDE_SIZE_POSCOLTEX
    #define SIZE_POS 3          // Number of position coordinates
    #define SIZE_COL 3          // Number of color coordinates
    #define SIZE_TEX 2          // Number of texture coordinates
    #define SIZE_STRIDE 8       // Total number of coordinates (data for each vertex)
#else
    #define SIZE_POS 3
    #define SIZE_COL 0
    #define SIZE_TEX 0
    #define SIZE_STRIDE 3
#endif

#include <stdarg.h>
#include "utility.h"
#include "geometry.h"

enum VDATA{
    POSITION,
    COLOR,
    TEXTURE
};

typedef unsigned int type_vertex_data_i[SIZE_STRIDE];

class Shape
{
private:
    unsigned int m_vertexCount;
    unsigned int *m_vertices;
    /*! Sets the specified attribute in one vertex of the array with the given data.
     * @param attribute VDATA enum (POSITION, COLOR or TEXTURE) attribute to set
     * @param vertex index of the vertex to be set.
     * @param data new data */
    void set_vdata(VDATA attribute, int vertex, Point &data);
public:
    Shape(const int n_vertices);
    ~Shape();
    void set_pos(Point data, int vertex);
    void set_color(Point data, int vertex);
    void set_texture(Point texture, int dest_vertex);
    unsigned get_vCount();
    unsigned *get_vArray();
};


class Rectangle : Shape
{
private:
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
    // int *get_vertex_data() { return vertex_data; }
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

                    ///                         ///
                    ///     NAMESPACE SHAPES    ///
                    ///                         ///
namespace shapes
{
    /* Returns the desired value divided by the ratio (Actual coordinate value in GL) */
    float proportion(float n);
    /* Returns the shape vertex data size in bytes (size of float) */              
    size_t vertex_buffer_sizef(Shape *shape); 
    /* Gets Shape's vertex (proportional) data to a given destination buffer array */
    float* get_vBuffer(float* destination, Shape &shape);
    /* Gets an element buffer to draw a rectangle using two triangles. Can inverst the diagonal using invert */
    unsigned int *get_eBuffer_rectangle(unsigned int *eBuffer, bool invert, int bLeft, int tLeft, int bRight, int tRight);
}

float shapes::proportion(float n){
    return n/PROPORTION;
}

size_t shapes::vertex_buffer_sizef(Shape *shape){
    return shape->get_vCount * SIZE_STRIDE * sizeof(float);
}

unsigned int *shapes::get_eBuffer_rectangle(unsigned int *eBuffer, bool invert, int bLeft, int tLeft, int bRight, int tRight){
        if(!invert){
        //// Diagonal
            eBuffer[0] = bLeft; 
            eBuffer[1] = tRight;
            eBuffer[3] = bLeft;
            eBuffer[4] = tRight;
        //// --------
            eBuffer[2] = tLeft;
            eBuffer[5] = bRight;
        }else{
            //// Diagonal
            eBuffer[0] = tLeft; 
            eBuffer[1] = bRight;
            eBuffer[3] = tLeft;
            eBuffer[4] = bRight;
        //// --------
            eBuffer[2] = bLeft;
            eBuffer[5] = tRight;
        }
    }

#endif