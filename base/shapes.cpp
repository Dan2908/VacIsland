#include "shapes.h"

Shape::Shape(Point p) : origin(p) {}
Shape::Shape(int x, int y) : origin(x, y) {}
float *Shape::get_normals(float dest[2]){
    memccpy(dest, &origin, 1, 2 *sizeof(float));
    return dest;
}

Rect::Rect(Point v1) : v1(v1) {}
Rect::Rect(Point v0, Point v1) : Shape(v0), v1(v1) {}

Triangle::Triangle(Point v1, Point v2, Point origin) : Shape(origin), v1(v1), v2(v2) {}
Triangle::Triangle() : Triangle({DEFAULT_SIZE,0}, {0,DEFAULT_SIZE}) {}

Rectangle::Rectangle() : v1({0,DEFAULT_SIZE}), v2({DEFAULT_SIZE,0}), v3({DEFAULT_SIZE,DEFAULT_SIZE}) {}
float *Rectangle::vertex_buffer_array(float *destArray){
    float res[VBO_STRIDE];
    util::copy_duff_device(this.origin, res, 2)
    util::copy_duff_device({1, 2}, destArray, VBO_STRIDE);
    return destArray;
}
VertexBuffer Rectangle::vertex_buffer() 
{
    float vertices[VBO_STRIDE * 4] = proportional({v0, v1, v2, v3});
}
ElementBuffer Rectangle::element_buffer(bool inverse)
{
    int indices[6] = (inverse ? {1, 2, 0, 1, 2, 3} : {0, 3, 1, 0, 3, 2});
    return ElementBuffer(indices, sizeof(indices), 3);
}


