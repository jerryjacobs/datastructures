#include <iostream>
#include <cstdlib>
#include <string>
#include "tetris.h"
using namespace std;

void copy(char* newa, char olda[], int newsize, int oldsize);

//constructor
Tetris::Tetris(int aWidth){
    width = aWidth;
    heights = new int[width];
    data = new char*[width];
    for (unsigned int i = 0; i < width; i++){
        heights[i] = 0;
        data[i] = new char[0];
    }
}
//returns width
int Tetris::get_width() const{
    return width;
}
//returns max height from heights array
int Tetris::get_max_height() const{
    int maxheight = 0;
    for (unsigned int i = 0; i < width; i++){
        if (heights[i] > maxheight){
            maxheight = heights[i];
        }
    }
    return maxheight;
}
//counts number of non space squares in the grid
int Tetris::count_squares() const{
    int count = 0;
    for (unsigned int i = 0; i < width; i++){
        for (unsigned int j = 0; j < heights[i]; j++){
            if (data[i][j] != ' '){
                count++;
            }
        }
    }
    return count;
}
//removes all the full rows in the grid and returns how many removed
int Tetris::remove_full_rows(){
    int minheight = get_max_height();
    for (unsigned int i = 0; i < width; i++){
        if (heights[i] < minheight){
            minheight = heights[i];
        }
    }
    int n = 0; //number of rows to remove
    char* remove = new char[get_max_height()]; //keeps track of which rows to remove
    for (unsigned int i = 0; i < get_max_height(); i++){
        remove[i] = 'K'; //keep row i
    }
    for (unsigned int r = 0; r < minheight; r++){
        int count = 0; //number of columns in the row that have a block
        for (unsigned int c = 0; c < width; c++){
            if (data[c][r] != ' '){
                count++;
            }
        }
        if (count == width){
            remove[r] = 'R'; //remove row
            n++;
        }
    }
    //build the temp array to match data but exclude 'R' rows
    char* temp;
    for (unsigned int c = 0; c < width; c++){
        temp = new char[heights[c]-n];
        int row_num = 0;
        for (unsigned int r = 0; r < heights[c]; r++){
            if (remove[r] == 'K'){
                temp[row_num] = data[c][r];
                row_num++;
            }
        }
        delete[] data[c];
        data[c] = temp;
        heights[c] -= n; //this is not the true value of heights[c]
    }
    //determine true value of heights[c]
    for (unsigned int c = 0; c < width; c++){
        int h = 0;
        for(unsigned int r = 0; r < heights[c]; r++){
            if (data[c][r] != ' '){
                h = r+1;
            }
        }
        heights[c] = h;
    }
    delete[] remove;
    return n;
}
/*The 4 column functions have the same algorithm:
 1) Create the new heights and new data arrays
 2) Run a loop to copy heights onto new heights and copy each array from data onto new data
 3) Run a loop to delete the arrays in data
 4) Delete data and heights completely
 5) Set data and heights to new data and new heights*/

//adds a column to left side of grid
void Tetris::add_left_column(){
    width += 1;
    int* new_heights = new int[width];
    char** new_data = new char*[width];
    new_heights[0] = 0;
    new_data[0] = new char[0];
    
    char* temp;
    for (unsigned int i = 1; i < width; i++){
        new_heights[i] = heights[i-1];
        temp = new char[heights[i-1]];
        copy(temp, data[i-1], heights[i-1], heights[i-1]);
        new_data[i] = temp;
    }
    for (unsigned int i = 0; i < width-1; i++){
        delete[] data[i];
    }
    delete[] data;
    delete[] heights;
    data = new_data;
    heights = new_heights;
}
//adds a column to right side of grid
void Tetris::add_right_column(){
    width += 1;
    int* new_heights = new int[width];
    char** new_data = new char*[width];
    new_heights[width-1] = 0;
    new_data[width-1] = new char[0];
    
    char* temp;
    for (unsigned int i = 0; i < width-1; i++){
        new_heights[i] = heights[i];
        temp = new char[heights[i]];
        copy(temp, data[i], heights[i], heights[i]);
        new_data[i] = temp;
    }
    for (unsigned int i = 0; i < width-1; i++){
        delete[] data[i];
    }
    delete[] data;
    delete[] heights;
    data = new_data;
    heights = new_heights;
}
//removes a column from the left side of grid
void Tetris::remove_left_column(){
    width -= 1;
    int* new_heights = new int[width];
    char** new_data = new char*[width];
    
    char*temp;
    for (unsigned int i = 0; i < width; i++){
        new_heights[i] = heights[i+1];
        temp = new char[heights[i+1]];
        copy(temp, data[i+1], heights[i+1], heights[i+1]);
        new_data[i] = temp;
    }
    for (unsigned int i = 0; i < width+1; i++){
        delete[] data[i];
    }
    delete[] data;
    delete[] heights;
    data = new_data;
    heights = new_heights;
}
//removes a column from the right side of grid
void Tetris::remove_right_column(){
    width -= 1;
    int* new_heights = new int[width];
    char** new_data = new char*[width];
    
    char* temp;
    for (unsigned int i = 0; i < width; i++){
        new_heights[i] = heights[i];
        temp = new char[heights[i]];
        copy(temp, data[i], heights[i], heights[i]);
        new_data[i] = temp;
    }
    for (unsigned int i = 0; i < width+1; i++){
        delete[] data[i];
    }
    delete[] data;
    delete[] heights;
    data = new_data;
    heights = new_heights;
}
//copies the old array onto the new array and fills the empty indexes with ' '
void copy(char* newa, char olda[], int newsize, int oldsize){
    for (unsigned int i = 0; i < oldsize; i++){
        newa[i] = olda[i];
    }
    for (unsigned int i = oldsize; i < newsize; i++){
        newa[i] = ' ';
    }
}
/*Adds a peice to the board based on type, rotation, and position
'temp' is a char array that replaces the array at data[i]
'h' is the highest kicker column WITH the offset from the shape of the type
 Each 'rotation block' (if rot ==) has the same basic algorithm:
 1) determine the kicker height 'h'
 2) copy the data array onto the temp array
 3) slightly modify the temp array based on shape type
 4) replace the data array with the temp array
 5) update heights array*/
void Tetris::add_piece(char type, int rot, int pos){
    char* temp;
    //I block
    if (type == 'I'){
        if(rot == 0 or rot == 180){
            temp = new char[heights[pos]+4];
            copy(temp, data[pos], heights[pos]+4, heights[pos]);
            temp[heights[pos]] = 'I';
            temp[heights[pos]+1] = 'I';
            temp[heights[pos]+2] = 'I';
            temp[heights[pos]+3] = 'I';
            delete[] data[pos];
            data[pos] = temp;
            heights[pos] += 4;
        }
        else{
            int h = 0;
            for (unsigned int i = pos; i < pos+4; i++){
                if (heights[i] > h){
                    h = heights[i];
                }
            }
            for (unsigned int i = pos; i < pos+4; i++){
                temp = new char[h+1];
                copy(temp, data[i], h+1, heights[i]);
                temp[h] = 'I';
                delete[] data[i];
                data[i] = temp;
                heights[i] = h+1;
            }
        }
    }
    //O block
    else if (type == 'O'){
        int h = 0;
        for (unsigned int i = pos; i < pos+2; i++){
            if (heights[i] > h){
                h = heights[i];
            }
        }
        for (unsigned int i = pos; i < pos+2; i++){
            temp = new char[h+2];
            copy(temp, data[i], h+2, heights[i]);
            temp[h] = 'O';
            temp[h+1] = 'O';
            delete[] data[i];
            data[i] = temp;
            heights[i] = h+2;
        }
    }
    //T block
    else if (type == 'T'){
        if (rot == 0){
            int h = 0;
            for (unsigned int i = pos; i < pos+3; i++){
                if (i != pos+1 and heights[i] > h){
                    h = heights[i];
                }
                else if (i == pos+1 and heights[i]+1 > h){
                    h = heights[i]+1;
                }
            }
            for (unsigned int i = pos; i < pos+3; i++){
                if (i != pos+1){
                    temp = new char[h+1];
                    copy(temp, data[i], h+1, heights[i]);
                    temp[h] = 'T';
                    delete[] data[i];
                    data[i] = temp;
                    heights[i] = h+1;
                }
                else{
                    temp = new char[h+1];
                    copy(temp, data[i], h+1, heights[i]);
                    temp[h-1] = 'T';
                    temp[h] = 'T';
                    delete[] data[i];
                    data[i] = temp;
                    heights[i] = h+1;
                }
            }
        }
        else if (rot == 90){
            int h;
            if (heights[pos] > heights[pos+1]+1){
                h = heights[pos];
            }
            else{
                h = heights[pos+1]+1;
            }
            temp = new char[h+1];
            copy(temp, data[pos], h+1, heights[pos]);
            temp[h] = 'T';
            delete[] data[pos];
            data[pos] = temp;
            heights[pos] = h+1;
            temp = new char[h+2];
            copy(temp, data[pos+1], h+2, heights[pos+1]);
            temp[h-1] = 'T';
            temp[h] = 'T';
            temp[h+1] = 'T';
            delete[] data[pos+1];
            data[pos+1] = temp;
            heights[pos+1] = h+2;
        }
        else if (rot == 180){
            int h = 0;
            for (unsigned int i = pos; i < pos+3; i++){
                if (heights[i] > h){
                    h = heights[i];
                }
            }
            for (unsigned int i = pos; i < pos+3; i++){
                if(i != pos+1){
                    temp = new char[h+1];
                    copy(temp, data[i], h+1, heights[i]);
                    temp[h] = 'T';
                    delete[] data[i];
                    data[i] = temp;
                    heights[i] = h+1;
                }
                else{
                    temp = new char[h+2];
                    copy(temp, data[i], h+2, heights[i]);
                    temp[h] = 'T';
                    temp[h+1] = 'T';
                    delete[] data[i];
                    data[i] = temp;
                    heights[i] = h+2;
                }
            }
        }
        else if (rot == 270){
            int h;
            if (heights[pos]+1 > heights[pos+1]){
                h = heights[pos]+1;
            }
            else{
                h = heights[pos+1];
            }
            temp = new char[h+2];
            copy(temp, data[pos], h+2, heights[pos]);
            temp[h-1] = 'T';
            temp[h] = 'T';
            temp[h+1] = 'T';
            delete[] data[pos];
            data[pos] = temp;
            heights[pos] = h+2;
            temp = new char[h+1];
            copy(temp, data[pos+1], h+1, heights[pos+1]);
            temp[h] = 'T';
            delete[] data[pos+1];
            data[pos+1] = temp;
            heights[pos+1] = h+1;
        }
    }
    //Z block
    else if (type == 'Z'){
        if (rot == 0 or rot == 180){
            int h = 0;
            for (unsigned int i = pos; i < pos+3; i++){
                if (i != pos and heights[i]+1 > h){
                    h = heights[i]+1;
                }
                else if (i == pos and heights[i] > h){
                    h = heights[i];
                }
            }
            temp = new char[h+1];
            copy(temp, data[pos], h+1, heights[pos]);
            temp[h] = 'Z';
            delete[] data[pos];
            data[pos] = temp;
            heights[pos] = h+1;
            temp = new char[h+1];
            copy(temp, data[pos+1], h+1, heights[pos+1]);
            temp[h-1] = 'Z';
            temp[h] = 'Z';
            delete[] data[pos+1];
            data[pos+1] = temp;
            heights[pos+1] = h+1;
            temp = new char[h];
            copy(temp, data[pos+2], h, heights[pos+2]);
            temp[h-1] = 'Z';
            delete[] data[pos+2];
            data[pos+2] = temp;
            heights[pos+2] = h;
        }
        else{
            int h;
            if (heights[pos]+1 > heights[pos+1]){
                h = heights[pos]+1;
            }
            else{
                h = heights[pos+1];
            }
            temp = new char[h+1];
            copy(temp, data[pos], h+1, heights[pos]);
            temp[h-1] = 'Z';
            temp[h] = 'Z';
            delete[] data[pos];
            data[pos] = temp;
            heights[pos] = h+1;
            temp = new char[h+2];
            copy(temp, data[pos+1], h+2, heights[pos+1]);
            temp[h] = 'Z';
            temp[h+1] = 'Z';
            delete[] data[pos+1];
            data[pos+1] = temp;
            heights[pos+1] = h+2;
        }
    }
    //S block
    else if (type == 'S'){
        if (rot == 0 or rot == 180){
            int h = 0;
            for (unsigned int i = pos; i < pos+3; i++){
                if (i != pos+2 and heights[i]+1 > h){
                    h = heights[i]+1;
                }
                else if (i == pos+2 and heights[i] > h){
                    h = heights[i];
                }
            }
            temp = new char[h];
            copy(temp, data[pos], h, heights[pos]);
            temp[h-1] = 'S';
            delete[] data[pos];
            data[pos] = temp;
            heights[pos] = h;
            temp = new char[h+1];
            copy(temp, data[pos+1], h+1, heights[pos+1]);
            temp[h-1] = 'S';
            temp[h] = 'S';
            delete[] data[pos+1];
            data[pos+1] = temp;
            heights[pos+1] = h+1;
            temp = new char[h+1];
            copy(temp, data[pos+2], h+1, heights[pos+2]);
            temp[h] = 'S';
            delete[] data[pos+2];
            data[pos+2] = temp;
            heights[pos+2] = h+1;
        }
        else{
            int h;
            if (heights[pos] > heights[pos+1]+1){
                h = heights[pos];
            }
            else{
                h = heights[pos+1]+1;
            }
            temp = new char[h+2];
            copy(temp, data[pos], h+2, heights[pos]);
            temp[h] = 'S';
            temp[h+1] = 'S';
            delete[] data[pos];
            data[pos] = temp;
            heights[pos] = h+2;
            temp = new char[h+1];
            copy(temp, data[pos+1], h+1, heights[pos+1]);
            temp[h-1] = 'S';
            temp[h] = 'S';
            delete[] data[pos+1];
            data[pos+1] = temp;
            heights[pos+1] = h+1;
        }
    }
    //L block
    else if (type == 'L'){
        if (rot == 0){
            int h;
            if (heights[pos] > heights[pos+1]){
                h = heights[pos];
            }
            else{
                h = heights[pos+1];
            }
            temp = new char[h+3];
            copy(temp, data[pos], h+3, heights[pos]);
            temp[h] = 'L';
            temp[h+1] = 'L';
            temp[h+2] = 'L';
            delete[] data[pos];
            data[pos] = temp;
            heights[pos] = h+3;
            temp = new char[h+1];
            copy(temp, data[pos+1], h+1, heights[pos+1]);
            temp[h] = 'L';
            delete[] data[pos+1];
            data[pos+1] = temp;
            heights[pos+1] = h+1;
        }
        else if (rot == 90){
            int h = 0;
            for (unsigned int i = pos; i < pos+3; i++){
                if (i != pos and heights[i] > h){
                    h = heights[i];
                }
                else if (i == pos and heights[i]+1 > h){
                    h = heights[i]+1;
                }
            }
            for (unsigned int i = pos; i < pos+3; i++){
                if (i != pos){
                    temp = new char[h+1];
                    copy(temp, data[i], h+1, heights[i]);
                    temp[h] = 'L';
                    delete[] data[i];
                    data[i] = temp;
                    heights[i] = h+1;
                }
                else{
                    temp = new char[h+1];
                    copy(temp, data[i], h+1, heights[i]);
                    temp[h-1] = 'L';
                    temp[h] = 'L';
                    delete[] data[i];
                    data[i] = temp;
                    heights[i] = h+1;
                }
            }
        }
        else if (rot == 180){
            int h;
            if (heights[pos] > heights[pos+1]+2){
                h = heights[pos];
            }
            else{
                h = heights[pos+1]+2;
            }
            temp = new char[h+1];
            copy(temp, data[pos], h+1, heights[pos]);
            temp[h] = 'L';
            delete[] data[pos];
            data[pos] = temp;
            heights[pos] = h+1;
            temp = new char[h+1];
            copy(temp, data[pos+1], h+1, heights[pos+1]);
            temp[h-2] = 'L';
            temp[h-1] = 'L';
            temp[h] = 'L';
            delete[] data[pos+1];
            data[pos+1] = temp;
            heights[pos+1] = h+1;
        }
        else if (rot == 270){
            int h = 0;
            for (unsigned int i = pos; i < pos+3; i++){
                if (heights[i] > h){
                    h = heights[i];
                }
            }
            for (unsigned int i = pos; i < pos+3; i++){
                if (i != pos+2){
                    temp = new char[h+1];
                    copy(temp, data[i], h+1, heights[i]);
                    temp[h] = 'L';
                    delete[] data[i];
                    data[i] = temp;
                    heights[i] = h+1;
                }
                else{
                    temp = new char[h+2];
                    copy(temp, data[i], h+2, heights[i]);
                    temp[h] = 'L';
                    temp[h+1] = 'L';
                    delete[] data[i];
                    data[i] = temp;
                    heights[i] = h+2;
                }
            }
        }
    }
    //J block
    else if (type == 'J'){
        if (rot == 0){
            int h;
            if (heights[pos] > heights[pos+1]){
                h = heights[pos];
            }
            else{
                h = heights[pos+1];
            }
            temp = new char[h+1];
            copy(temp, data[pos], h+1, heights[pos]);
            temp[h] = 'J';
            delete[] data[pos];
            data[pos] = temp;
            heights[pos] = h+1;
            temp = new char[h+3];
            copy(temp, data[pos+1], h+3, heights[pos+1]);
            temp[h] = 'J';
            temp[h+1] = 'J';
            temp[h+2] = 'J';
            delete[] data[pos+1];
            data[pos+1] = temp;
            heights[pos+1] = h+3;
        }
        else if (rot == 90){
            int h = 0;
            for (unsigned int i = pos; i < pos+3; i++){
                if (heights[i] > h){
                    h = heights[i];
                }
            }
            for (unsigned int i = pos; i < pos+3; i++){
                if (i != pos){
                    temp = new char[h+1];
                    copy(temp, data[i], h+1, heights[i]);
                    temp[h] = 'J';
                    delete[] data[i];
                    data[i] = temp;
                    heights[i] = h+1;
                }
                else{
                    temp = new char[h+2];
                    copy(temp, data[i], h+2, heights[i]);
                    temp[h] = 'J';
                    temp[h+1] = 'J';
                    delete[] data[i];
                    data[i] = temp;
                    heights[i] = h+2;
                }
            }
        }
        else if (rot == 180){
            int h;
            if (heights[pos]+2 > heights[pos+1]){
                h = heights[pos]+2;
            }
            else{
                h = heights[pos+1];
            }
            temp = new char[h+1];
            copy(temp, data[pos], h+1, heights[pos]);
            temp[h-2] = 'J';
            temp[h-1] = 'J';
            temp[h] = 'J';
            delete[] data[pos];
            data[pos] = temp;
            heights[pos] = h+1;
            temp = new char[h+1];
            copy(temp, data[pos+1], h+1, heights[pos+1]);
            temp[h] = 'J';
            delete[] data[pos+1];
            data[pos+1] = temp;
            heights[pos+1] = h+1;
        }
        else if (rot == 270){
            int h = 0;
            for (unsigned int i = pos; i < pos+3; i++){
                if (i != pos+2 and heights[i] > h){
                    h = heights[i];
                }
                else if (i == pos+2 and heights[i]+1 > h){
                    h = heights[i]+1;
                }
            }
            for (unsigned int i = pos; i < pos+3; i++){
                if (i != pos+2){
                    temp = new char[h+1];
                    copy(temp, data[i], h+1, heights[i]);
                    temp[h] = 'J';
                    delete[] data[i];
                    data[i] = temp;
                    heights[i] = h+1;
                }
                else{
                    temp = new char[h+1];
                    copy(temp, data[i], h+1, heights[i]);
                    temp[h-1] = 'J';
                    temp[h] = 'J';
                    delete[] data[i];
                    data[i] = temp;
                    heights[i] = h+1;
                }
            }
        }
    }
}
void Tetris::destroy(){
    for (unsigned int i = 0; i < width; i++){
        delete[] data[i];
    }
    delete[] data;
    delete[] heights;
}