#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class Tetris {
public:
    Tetris(int aWidth);
    int get_width() const;
    int get_max_height() const;
    int count_squares() const;
    int remove_full_rows();
    void add_left_column();
    void add_right_column();
    void remove_left_column();
    void remove_right_column();
    void add_piece(char type, int rot, int pos);
    void destroy();
    void print() const;
private:
    int width;
    int *heights;
    char** data;
};