#ifndef SHAPES_H
#define SHAPES_H

#include <cstdlib>
#include "geometry.h"
#include "../glFunc.h"

static unsigned int PROPORTION = 1000;

class Shape
{
private:
    Point origin;
public:
    Shape(Point p);
    Shape(int x = 0, int y = 0);
    t_VBO_stride 
};

Shape::Shape(Point p) : origin(p) {}
Shape::Shape(int x = 0, int y = 0) : origin(x, y) {}

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

Triangle::Triangle(Point v1, Point v2, Point origin) : Shape(v0), v1(v1), v2(v2) {}
Triangle::Triangle() : Triangle({1,0}, {0,1}) {}

class Rectangle : Shape
{
private:
    Point v1, v2, v3;
public:
    Rectangle();
    VertexBuffer vertex_buffer();
    ElementBuffer element_buffer(bool inverse);
};

Rectangle::Rectangle() : v1({0,1}), v2({1,0}, v2({1,1}) {}
VertexBuffer Rectangle::vertex_buffer() {
    float vertices[VBO_STRIDE * 4] = {v0.x, v0.y
}

ElementBuffer Rectangle::element_buffer(bool inverse)
{
    int indices[6] = (inverse ? {1, 2, 0, 1, 2, 3} : {0, 3, 1, 0, 3, 2});
    return ElementBuffer(indices, sizeof(indices), 3);
}



#endif