#include "shapes.h"

                    /// SHAPE ///

Shape::Shape(const int n_vertices) : m_vertexCount(n_vertices) {
    m_vertices = (unsigned *)calloc(n_vertices, sizeof(type_vertex_data_i)); }

Shape::~Shape() { free(m_vertices); }

void Shape::set_vdata(VDATA attribute, int vertex, Point &data){
    unsigned int *ptr = m_vertices + vertex * SIZE_STRIDE; // get to the vertex;
    int data_size;                                          //data size

    switch (attribute){
    case POSITION:
        data_size = SIZE_POS;
        break;
    case COLOR:
        data_size = SIZE_COL;
        ptr += SIZE_POS;
        break;
    case TEXTURE:
        data_size = SIZE_TEX;
        ptr += SIZE_POS + SIZE_COL;
    }

    ptr += attribute * SIZE_POS;
    memcpy(ptr, data.coords, data_size * sizeof(unsigned int));
}

void Shape::set_pos(Point pos, int dest_vertex)         { set_vdata(POSITION, dest_vertex, pos); }

void Shape::set_color(Point color, int dest_vertex)     { set_vdata(COLOR, dest_vertex, color); }

void Shape::set_texture(Point texture, int dest_vertex) { set_vdata(TEXTURE, dest_vertex, texture); }

unsigned Shape::get_vCount() { return m_vertexCount; }

unsigned *Shape::get_vArray() { return m_vertices; }

                        /// RECTANGLE ///

Rectangle::Rectangle() : Rectangle(PROPORTION) {}
Rectangle::Rectangle(int square_size) : Rectangle(square_size, square_size) {}
Rectangle::Rectangle(int w, int h) : Shape(4)
{
    set_pos(Point(0, 0, 0), 0);
    set_pos(Point(0, h, 0), 2);
    set_pos(Point(w, 0, 0), 1);
    set_pos(Point(w, h, 0), 3);
}
Rectangle::Rectangle(int w, int h, Point offset) : Shape(4)
{
    set_pos(Point(offset.get_x(), offset.get_y(), offset.get_z()), 0);
    set_pos(Point(offset.get_x(), h + offset.get_y(), offset.get_z()), 1);
    set_pos(Point(w + offset.get_x(), offset.get_y(), offset.get_z()), 2);
    set_pos(Point(w + offset.get_x(), h + offset.get_y(), offset.get_z()), 3);
}

Surface::Surface() : Shape(4) {}
Surface::Surface(int squares_w, int squares_h, int square_size)
    : Shape((squares_w + 1) * (squares_h + 1)), m_width(squares_w), m_height(squares_h){
    
    unsigned *ptr = m_vertices;

    for (int x = 0; x <= (m_width * square_size); x += square_size){
        for (int y = 0; y <= (m_height * square_size); y += square_size){
            *ptr++ = x;
            *ptr++ = y;
             ptr += SIZE_STRIDE - 2; //skip to the next vertex
        }
    }
}
unsigned Surface::get_square_count() const{
    return m_width * m_height;
}


float shapes::proportion(float n){
    return n/PROPORTION;
}

size_t shapes::vertex_buffer_sizef(Shape *shape){
    return shape->get_vCount() * SIZE_STRIDE * sizeof(float);
}

float* shapes::get_vBuffer(float* vBuffer, Shape &shape){
    size_t count = vertex_buffer_sizef(&shape);
    util::copy_duff_device(shape.get_vArray(), vBuffer, count);
    util::operate_duff_device(vBuffer, count, proportion);
    return vBuffer;
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
    return eBuffer;
}

unsigned int *shapes::get_eBuffer_surface(unsigned int *eBuffer, Surface &surface){
    unsigned int *ptr = (unsigned*)malloc(6 * surface.get_vCount());
}

shapes::vArray::vArray(Shape &shape){
    array = (float*)malloc(vertex_buffer_sizef(&shape));
    get_vBuffer(array, shape);
}

float *shapes::vArray::get_vertex_data(unsigned vertex){
    return &array[vertex * SIZE_STRIDE];
}

