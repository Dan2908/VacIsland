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

void gen_square_grid(float *destiny, unsigned int width, unsigned int height, float size){
    const int col_offset = width+1;

    for(unsigned h = 0; h <= height; h++){
        for(unsigned w = 0; w <= width; w++){
            int x_pos = 8 * (w + h*col_offset);
            destiny[x_pos]      = w*size;        // X
            destiny[x_pos + 1]  = h*size;        // Y
        }
    }
}

void gen_triangles(unsigned int *destiny, unsigned int width, unsigned int height){
    for(int h = 0; h < height; h++){
        for(int w = 0; w < width; w++){
            int val = (w + h*width),
                pos = 6 * val; 

            destiny[pos]     = val;                     // A
            destiny[pos + 1] = val + 1;                 // B
            destiny[pos + 2] = val + width + 1;         // C

            destiny[pos + 3] = val + width + 2;         // D
            destiny[pos + 4] = val + width + 1;         // C
            destiny[pos + 5] = val + 1;                 // B
        }
    }
}

int main(){
    int H = 10, W = 10;
    float p[8 * (W+1) * (H+1)];
    unsigned indexes[6*W*H];

    gen_square_grid(p, W, H, 0.2f);
    gen_triangles(indexes, W, H);

    for(int i = 0; i < H; i++){
        printf("%d -> ", i);
        for(int j = 0; j < 6*W; j++){
            printf("%d ", indexes[i*W + j]);
        }
        printf("\n");
    }
    LOG("\n . ");

    for(unsigned h = 0; h <= H; h++){
        for(unsigned w = 0; w <= W; w++){
            unsigned x_pos = 8 * (h*(W+1) + w);
            printf("{%.2f, %.2f} ", p[x_pos], p[x_pos + 1]);
        }
        std::cout << "\n\n";
    }


    /*
    Point a( m_pos(-0.5f, -0.5f) );
    Point b = a , c = a;
    b.translate( m_pos(0.0f, 1.0f) );
    c.translate( m_pos(1.0f, 0.0f) );

    LOG(&a << " : " << &b);
    LOG("{" << a.get_pos().x << ", " << a.get_pos().y << ", " << a.get_pos().z  << "}");
    LOG("{" << b.get_pos().x << ", " << b.get_pos().y << ", " << b.get_pos().z  << "}");
    LOG("{" << c.get_pos().x << ", " << c.get_pos().y << ", " << c.get_pos().z  << "}");
    */

    return EXIT_SUCCESS;
}