#include "shapes.h"

float normalize(float n){
    return n/s_ratio;
}

Shape::Shape(const int n_vertices) : n_vertices(n_vertices){
    vertex_data = (int*)calloc(n_vertices, sizeof(VertexDatai));
}
void Shape::set_pos(Point pos, int dest_vertex){
    int offset = dest_vertex*s_stride;
    memcpy((vertex_data + offset), pos.coords, size_i_3D);
}

void Shape::set_color(Point color, int dest_vertex){
    int offset = dest_vertex*s_stride + s_vertices;
    memcpy((vertex_data + offset), color.coords, size_i_3D);
}
void Shape::set_texture(Point tex_coord, int dest_vertex){
    int offset = dest_vertex*s_stride + s_vertices + s_color;
    memcpy((vertex_data + offset), tex_coord.coords, size_i_2D);
}


Rectangle::Rectangle() : Shape(4) 
{
    set_pos(Point(0, 0, 0), 0);
    set_pos(Point(s_ratio, 0, 0), 1);
    set_pos(Point(0, s_ratio, 0), 2);
    set_pos(Point(s_ratio, s_ratio, 0), 3);
}

float *Rectangle::vertex_buffer(float *dest){
    util::copy_duff_device(vertex_data, dest, n_vertices * s_stride);
    util::operate_duff_device(dest, n_vertices * s_stride, normalize);
    return dest;
}



