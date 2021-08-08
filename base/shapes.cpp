#include "shapes.h"



Shape::Shape(const int n_vertices) : m_vertexCount(n_vertices)
{
    m_vertices = (unsigned *)calloc(n_vertices, sizeof(type_vertex_data_i));
}

Shape::~Shape() { free(m_vertices); }

void Shape::set_vdata(VDATA attribute, int vertex, Point &data)
{
    unsigned int *ptr = m_vertices + vertex * SIZE_STRIDE; // get to the vertex;
    int data_size;                                          //data size

    switch (attribute)
    {
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

void Shape::set_pos(Point pos, int dest_vertex)
{
    set_vdata(POSITION, dest_vertex, pos);
}

void Shape::set_color(Point color, int dest_vertex)
{
    set_vdata(COLOR, dest_vertex, color);
}
void Shape::set_texture(Point texture, int dest_vertex)
{
    set_vdata(TEXTURE, dest_vertex, texture);
}

unsigned Shape::get_vCount() { return m_vertexCount; }
unsigned *Shape::get_vArray() { return m_vertices; }

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
unsigned int *Rectangle::element_buffer(bool reverse_order, unsigned int *dest)
{
    if (!reverse_order)
    {
        dest[0] = 0;
        dest[3] = 0; //    /|  ; |''/
        dest[1] = 3;
        dest[4] = 3; //   / |  ; | /
        dest[2] = 2;
        dest[5] = 1; //  /__|  ; |/
    }
    else
    {
        dest[0] = 1;
        dest[3] = 1; //  |\    ; \''|
        dest[1] = 2;
        dest[4] = 2; //  | \   ;  \ |
        dest[2] = 0;
        dest[5] = 3; //  |__\  ;   \|
    }
    return dest;
}
void Rectangle::get_buffer_data(float *vertex_array, unsigned int *element_array, bool reverse_order)
{
    vertex_buffer(vertex_array);
    element_buffer(reverse_order, element_array);
}

Surface::Surface() : Shape(3) {}
Surface::Surface(int squares_w, int squares_h, int square_size)
    : Shape((squares_w + 1) * (squares_h + 1)), m_width(squares_w), m_height(squares_h)
{
    int *ptr = vertex_data;

    for (int x = 0; x <= (m_width * square_size); x += square_size)
    {
        for (int y = 0; y <= (m_height * square_size); y += square_size)
        {
            *ptr++ = x;
            *ptr++ = y;
            ptr += s_stride - 2; //skip to the next vertex
        }
    }
}

#define RECTANGLE(x, H)                          \
    {                                            \
        x, x + 1, x + H, x + 1, x + H, x + H + 1 \
    }

unsigned int *Surface::element_buffer(int w, int h, unsigned int *dest)
{
    for (int x = 0; x < m_width; x++)
    {
        for (int y = 0; y < m_height; y++)
        {
            unsigned int rectangle[] = RECTANGLE((unsigned)(x * m_height + y), m_height);
            util::copy_duff_device(rectangle, dest, 6);
        }
    }
    return dest;
}

void Surface::get_buffer_data(float *vertex_array, unsigned int *element_array, bool reverse_order)
{
    vertex_buffer(vertex_array);
    element_buffer(m_width, m_height, element_array);
}

#undef RECTANGLE
