#include "shapes.h"

float *get_normal(float *dest, Point p){
    *dest++ = p.x / PROPORTION;
    *dest++ = p.y / PROPORTION;
    *dest++ = p.z / PROPORTION;
    return dest;
}

float *get_normals(float *dest, int n ...){
    va_list vl;
    va_start(vl, n);
    for(int i = 0; i < n; i++){
        get_normals(dest, va_arg(vl, int));
    }
    va_end(vl);
    return dest;
}

Shape::Shape() : n_vertices(0), vertex_data(nullptr) {}
float *Shape::get_vertex_array(VertexDataf dest)
{
    util::copy_duff_device(vertex_data, dest, n_vertices, static_cast<float>());
    return dest;
}

Rect::Rect(Point v1) : v1(v1) {}
Rect::Rect(Point v0, Point v1) : Shape(v0), v1(v1) {}

Triangle::Triangle(Point v1, Point v2, Point origin) : Shape(origin), v1(v1), v2(v2) {}
Triangle::Triangle() : Triangle({DEFAULT_SIZE,0}, {0,DEFAULT_SIZE}) {}

Rectangle::Rectangle() : v1({0,DEFAULT_SIZE}), v2({DEFAULT_SIZE,0}), v3({DEFAULT_SIZE,DEFAULT_SIZE}) {}
float *Rectangle::vertex_buffer(float *dest){
    get_normals(dest, 4, origin, v1, v2, v3);
    return dest;
}



