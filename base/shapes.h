#ifndef SHAPES_H
#define SHAPES_H

#include <cstdlib>
#include "geometry.h"
#include "../glFunc.h"

static unsigned int PROPORTION = 1000;
static unsigned int DEFAULT_SIZE = 1000;

template<typename T, typename U>
T proportional(U x){ return (T)(x/PROPORTION); }

class Shape
{
private:
    Point origin;
public:
    Shape(Point p);
    Shape(int x = 0, int y = 0);
};

Shape::Shape(Point p) : origin(p) {}
Shape::Shape(int x, int y) : origin(x, y) {}

class Rect : Shape
{
private:
    Point v1;
public:
    Rect(Point v1);
    Rect(Point v0, Point v1);
};

Rect::Rect(Point v1) : v1(v1) {}
Rect::Rect(Point v0, Point v1) : Shape(v0), v1(v1) {}

class Triangle : Shape
{
private:
    Point v1, v2;
public:
    Triangle();
    Triangle(Point v1, Point v2, Point v0 = 0);
};

Triangle::Triangle(Point v1, Point v2, Point origin) : Shape(origin), v1(v1), v2(v2) {}
Triangle::Triangle() : Triangle({DEFAULT_SIZE,0}, {0,DEFAULT_SIZE}) {}

class Rectangle : Shape
{
private:
    Point v1, v2, v3;
public:
    Rectangle();
    VertexBuffer vertex_buffer();
    float *vertex_buffer_array();
    ElementBuffer element_buffer(bool inverse);
};

Rectangle::Rectangle() : v1({0,DEFAULT_SIZE}), v2({DEFAULT_SIZE,0}, v2({DEFAULT_SIZE,DEFAULT_SIZE}) {}

VertexBuffer Rectangle::vertex_buffer() 
{
    float vertices[VBO_STRIDE * 4] = proportional({v0, v1, v2, v3});
}



ElementBuffer Rectangle::element_buffer(bool inverse)
{
    int indices[6] = (inverse ? {1, 2, 0, 1, 2, 3} : {0, 3, 1, 0, 3, 2});
    return ElementBuffer(indices, sizeof(indices), 3);
}



#endif