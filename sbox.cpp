#include <iostream>
#include <fstream>

#define LOG(...) std::cerr << __VA_ARGS__ << std::endl

template<typename T>
struct m_pos{
    T x, y, z;
    m_pos(T x, T y, T z) : x(x), y(y), z(z) {}
    m_pos(T x, T y) : x(x), y(y), z(0) {}
    ~m_pos() {}
    m_pos<T> operator+(m_pos<T> A){
        return m_pos<T>(x + A.x, y + A.y, z + A.z);
    }
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
    m_pos<T> get_pos(){
        return m_pos<T>(arr_PCT[0], arr_PCT[1], arr_PCT[2]);
    }
    Point* copy(m_pos<T> offset){
        Point *ret = new Point();
        ret->arr_PCT = arr_PCT;
        LOG(offset.y << " <--");
        ret->set_pos(offset + get_pos());
        return ret;
    }
};


const char *path = "res/asset/cube.dat";

void get_point(){

}

int main(){
    Point<float> p( m_pos<float>(1, -7, -7) );

    Point<float> *r = p.copy( m_pos<float>(0.0f, 1.5f, 0.0f) );

    for(int i = 0; i < 8; i++){
        LOG(r->getArray()[i]);
    }
    return EXIT_SUCCESS;
}