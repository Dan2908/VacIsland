#include "shapes.h"

float normalize(float n){
    return n/s_ratio;
}

Shape::Shape(const int n_vertices) : m_vertexCount(n_vertices){
    m_vertices = (unsigned int*)calloc(n_vertices, sizeof(VertexDatai));
}
void Shape::set_pos(Point data, int vertex){
    shapes::set_vdata(m_vertices, 3, vertex, data);
}
void Shape::set_color(Point data, int dest_vertex){
    shapes::set_vdata(m_vertices, 3, vertex, data);
}
void Shape::set_texture(Point tex_coord, int dest_vertex){
    int offset = dest_vertex*s_stride + s_vertices + s_color;
    memcpy((vertex_data + offset), tex_coord.coords, size_i_2D);
}
size_t Shape::vertex_buffer_size(){
    return n_vertices * s_stride * sizeof(float);
}
long long Shape::element_buffer_size(){
    return (n_vertices > 2) ?       // if 3 or more vertices, the shape can be made or triangles (3). Otherwise, one or two points.
                            (3 * (n_vertices - 2) * sizeof(unsigned int)) : // triangles (3) each vertice greater than (2) * size of int
                            (n_vertices * sizeof(unsigned int));            // one element per vertice;
}
float *Shape::vertex_buffer(float *dest){
    util::copy_duff_device(vertex_data, dest, n_vertices * s_stride);
    util::operate_duff_device(dest, n_vertices * s_stride, normalize);
    return dest;
}

Rectangle::Rectangle() : Rectangle(s_ratio) {}
Rectangle::Rectangle(int square_size) : Rectangle(square_size, square_size) {}
Rectangle::Rectangle(int w, int h) : Shape(4) 
{
    set_pos(Point(0, 0, 0), 0);
    set_pos(Point(0, h, 0), 2);
    set_pos(Point(w, 0, 0), 1);
    set_pos(Point(w, h, 0), 3);
}
Rectangle::Rectangle(int w, int h, Point offset) : Shape(4) {
    set_pos(Point(    offset.get_x(),       offset.get_y(), offset.get_z()), 0);
    set_pos(Point(    offset.get_x(),   h + offset.get_y(), offset.get_z()), 1);
    set_pos(Point(w + offset.get_x(),       offset.get_y(), offset.get_z()), 2);
    set_pos(Point(w + offset.get_x(),   h + offset.get_y(), offset.get_z()), 3);
}
unsigned int *Rectangle::element_buffer(bool reverse_order, unsigned int *dest){
    if(!reverse_order){
        dest[0] = 0; dest[3] = 0;   //    /|  ; |''/
        dest[1] = 3; dest[4] = 3;   //   / |  ; | /
        dest[2] = 2; dest[5] = 1;   //  /__|  ; |/
    }
    else{
        dest[0] = 1; dest[3] = 1;   //  |\    ; \''|
        dest[1] = 2; dest[4] = 2;   //  | \   ;  \ |
        dest[2] = 0; dest[5] = 3;   //  |__\  ;   \|
    }
    return dest;
}
void Rectangle::get_buffer_data(float *vertex_array, unsigned int *element_array, bool reverse_order){
    vertex_buffer(vertex_array);
    element_buffer(reverse_order, element_array);
}

Surface::Surface() : Shape(3) {}
Surface::Surface(int squares_w, int squares_h, int square_size) : Shape( (squares_w + 1) * (squares_h + 1)){
    int *ptr     = vertex_data,
        W        = squares_w * square_size,
        H        = squares_h * square_size;

    for(int x = 0; x <= W; x += square_size){
        for(int y = 0; y <= H; y += square_size){
            *ptr++ = x;
            *ptr++ = y;
            ptr += s_stride - 2;    //skip to the next vertex
        }
    }
}


