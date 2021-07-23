#include <iostream>
#include <fstream>

#define LOG(...) std::cerr << __VA_ARGS__ << std::endl

template<typename T>
struct m_pos{
    int x, y, z;
    m_pos(T x, T y, T z) : x(x), y(y), z(z) {}
    m_pos(T x, T y) : x(x), y(y), z(0) {}
    ~m_pos() {}
};

template<typename T>
class Point{
    T *arr_PCT; // positions(3) colors(3) texture(2)
public:
    Point()             : arr_PCT((T*)calloc(8, sizeof(T))) 
    {}
    Point(m_pos<T> pos) : Point()
    { 
        set_pos(pos); 
    }
    ~Point() 
    { 
        free(arr_PCT);
    }
    // methods //
    T* getArray()
    {
        return arr_PCT;
    }
    void set_pos(m_pos<T> pos){
        arr_PCT[0] = pos.x;
        arr_PCT[1] = pos.y;
        arr_PCT[2] = pos.z;
    }
    void set_color(m_pos<T> color){
        arr_PCT[3] = color.x;
        arr_PCT[4] = color.y;
        arr_PCT[5] = color.z;
    }
    void set_texture(m_pos<T> texture){
        arr_PCT[6] = texture.x;
        arr_PCT[7] = texture.y;
    }
    T* project_point(){
        T *ret(this);
    }
};


const char *path = "res/asset/cube.dat";

void get_point(){

}

int main(){
    Point<float> p(m_pos<float>(1, -7, -7));

    for(int i = 0; i < 8; i++){
        LOG(p.getArray()[i]);
    }
    return EXIT_SUCCESS;
}