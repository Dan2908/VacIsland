#ifndef GEOMETRY_H
#define GEOMETRY_H

typedef int arr_p[3];

const short size_i_2D = 2 * sizeof(int); // size of 2 int
const short size_i_3D = 3 * sizeof(int); // size of 2 int

enum cardinals{
    X, Y, Z
};

struct Point{ 
    arr_p coords;
    Point(int x = 0, int y = 0, int z = 0) : coords {x, y, z} {}
    int get_x() { return coords[X]; }
    int get_y() { return coords[Y]; }
    int get_z() { return coords[Z]; }
};

struct Dimension
{
    unsigned int width,
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