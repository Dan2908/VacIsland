#include <iostream>
#include <fstream>

#define LOG(...) std::cerr << __VA_ARGS__ << std::endl

class m_pos{
public:
    float x, y, z;
    m_pos(float x, float y, float z) : x(x), y(y), z(z) {}
    m_pos(float x, float y) : x(x), y(y), z(0) {}
    ~m_pos() {}
    friend m_pos operator+(m_pos one, m_pos other){
        return m_pos(one.x + other.x, one.y + other.y, one.z + other.z);
    }
};

class Point{
    float *arr_PCT; // positions(3) colors(3) texture(2)
public:
    Point()             : arr_PCT((float*)calloc(8, sizeof(float))) 
    {}
    Point(m_pos pos) : Point()
    { 
        set_pos(pos); 
    }
    Point(const Point &p) : Point() { memcpy(arr_PCT, p.arr_PCT, sizeof(float) * 8); }
    ~Point() 
    { 
        free(arr_PCT);
    }
    // methods //
    float* getArray()
    {
        return arr_PCT;
    }
    void set_pos(m_pos pos){
        arr_PCT[0] = pos.x;
        arr_PCT[1] = pos.y;
        arr_PCT[2] = pos.z;
    }
    void set_color(m_pos color){
        arr_PCT[3] = color.x;
        arr_PCT[4] = color.y;
        arr_PCT[5] = color.z;
    }
    void set_texture(m_pos texture){
        arr_PCT[6] = texture.x;
        arr_PCT[7] = texture.y;
    }
    m_pos get_pos(){
        return m_pos(arr_PCT[0], arr_PCT[1], arr_PCT[2]);
    }
    void translate(m_pos pos){
        set_pos(pos + get_pos());
    }
};

const char *path = "res/asset/cube.dat";

int main(){
    Point a( m_pos(-0.5f, -0.5f) );
    Point b = a , c = a;
    b.translate( m_pos(0.0f, 1.0f) );
    c.translate( m_pos(1.0f, 0.0f) );

    LOG(&a << " : " << &b);
    LOG("{" << a.get_pos().x << ", " << a.get_pos().y << ", " << a.get_pos().z  << "}");
    LOG("{" << b.get_pos().x << ", " << b.get_pos().y << ", " << b.get_pos().z  << "}");
    LOG("{" << c.get_pos().x << ", " << c.get_pos().y << ", " << c.get_pos().z  << "}");

    return EXIT_SUCCESS;
}