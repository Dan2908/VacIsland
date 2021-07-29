#ifndef GEOMETRY_H
#define GEOMETRY_H

struct Point{ 
    int x;
    int y; 
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

struct Dimension
{
    unsigned int width;
                 height;
    Dimension(unsigned int w, unsigned int h) : width(w), height(h) {}

    bool operator<(const Dimension &other){
        return (width + height) < (other.width + other.height);
    }
    bool operator==(const Dimension &other){
        return (width == other.width) && (height == other.height);
    }
};

#endif