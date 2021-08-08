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
typedef float        type_vertex_data_f[SIZE_STRIDE];

class Shape{
protected:
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

class Rectangle : public Shape{
public:
    Rectangle();
    Rectangle(int square_size);
    Rectangle(int w, int h);
    Rectangle(int w, int h, Point offset);
};

class Surface : public Shape{
private:
    unsigned m_width, m_height;
public:
    Surface();
    /** Create a square 2d surface (z = 0) made up of squares 
     * @param squares_w Number of squares if width.
     * @param squares_h Number of squares if height.
     * @param squares_size Size of each square's side. */
    Surface(int squares_w, int squares_h, int square_size);
    unsigned get_square_count() const;
};

                    ///                         ///
                    ///     NAMESPACE SHAPES    ///
                    ///                         ///
namespace shapes
{
    /* Returns the desired value divided by the ratio (Actual coordinate value in GL) */
    float proportion(float n);
    /* Returns the shape vertex data size in bytes (size of float) */              
    size_t vertex_buffer_sizef(Shape *shape); 
    /* Gets Shape's vertex (proportional) data to a given vBuffer array */
    float* get_vBuffer(float* vBuffer, Shape &shape);
    /* Gets an element buffer to draw a rectangle using two triangles. Can invert the diagonal using invert */
    unsigned int *get_eBuffer_rectangle(unsigned int *eBuffer, bool invert, int bLeft, int tLeft, int bRight, int tRight);

    unsigned int *get_eBuffer_surface(unsigned int *eBuffer, Surface &surface);

    class vArray{
    private:
        float *array;
    public:
        vArray(Shape &shape);
        virtual float *get_array() {return array; }
        virtual float *get_vertex_data(unsigned vertex);
    };

    class eArray : public vArray{
    private:
        unsigned *array;
    public:
        eArray(Shape &shape);

        unsigned *get_element_data();
    };
}

#endif