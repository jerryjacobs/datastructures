//
//  main.cpp
//  Homework 1
//
//  Created by Jerry Jacobs on 1/30/16.
//  Copyright © 2016 Jerry Jacobs. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;

//replaces the target character with the sub character for all positions
vector<string> replace(vector<string> &vec, char target, char sub) {
    for (unsigned int i = 0; i < vec.size(); i++) {
        for (unsigned int j = 0; j < vec[i].size(); j++){
            if (vec[i][j] == target){
                vec[i][j] = sub;
            }
        }
    }
    return vec;
}
//expands the boundary of all clusters with target character
vector<string> dilation(vector<string> &vec, char target){
    vector<string> dilated = vec;
    for (unsigned int i = 0; i < vec.size(); i++){
        for (unsigned int j = 0; j < vec[i].size(); j++){
            //If position isnt target char and one of the 4 adjacent positions is: make it target char
            if ((vec[i][j] != target) and ( (i > 0 and vec[i-1][j] == target) or \
                                            (i < vec.size()-1 and vec[i+1][j] == target) or \
                                            (j > 0 and vec[i][j-1] == target) or \
                                            (j < vec[i].size()-1 and vec[i][j+1] == target))){
                dilated[i][j] = target;
            }
        }
    }
    return dilated;
}
//compresses the boundary of clusters with target character
vector<string> erosion(vector<string> &vec, char target, char back){
    vector<string> eroded = vec;
    for (unsigned int i = 0; i < vec.size(); i++){
        for (unsigned int j = 0; j < vec[i].size(); j++){
            //If position is target char and one of the 4 adjacent positions isnt: make it back char
            if ((vec[i][j] == target) and ( (i > 0 and vec[i-1][j] != target) or \
                                            (i < vec.size()-1 and vec[i+1][j] != target) or \
                                            (j > 0 and vec[i][j-1] != target) or \
                                            (j < vec[i].size()-1 and vec[i][j+1] != target))){
                eroded[i][j] = back;
            }
        }
    }
    return eroded;
}
//replaces cluster at (row r, column c) with sub char by recursively checking adjacent positions
void floodfill(vector<string> &vec, unsigned int r, unsigned int c, char sub){
    char target = vec[r][c];
    vec[r][c] = sub;
    if (r > 0 and vec[r-1][c] == target){
        floodfill(vec, r-1, c, sub);
    }
    if (r < vec.size()-1 and vec[r+1][c] == target){
        floodfill(vec, r+1, c, sub);
    }
    if (c > 0 and vec[r][c-1] == target){
        floodfill(vec, r, c-1, sub);
    }
    if (c < vec[r].size()-1 and vec[r][c+1] == target){
        floodfill(vec, r, c+1, sub);
    }
}

int main(int argc, char * argv[]) {
    //needs between 5-7 arguments
    if (argc < 5 or argc > 7) {
        cerr << "Needs between 5-7 arguments" << endl << "Has " << argc << " arguments" << endl;
        return 1;
    }
    //checks input file is valid
    ifstream input(argv[1]);
    if (!input.good()) {
        cerr << "Cannot open the file" << endl;
        return 2;
    }
    //reads input file line by line and stores into vector
    string line;
    vector<string> lines;
    while (input >> line) {
        lines.push_back(line);
    }
    //determines the new vector to output based on command line argument
    vector<string> final;
    if (argv[3] == string("replace")) {
        final = replace(lines, argv[4][0], argv[5][0]);
    }
    else if (argv[3] == string("dilation")) {
        final = dilation(lines, argv[4][0]);
    }
    else if (argv[3] == string("erosion")) {
        final = erosion(lines, argv[4][0], argv[5][0]);
    }
    else if (argv[3] == string("floodfill")) {
        floodfill(lines, atoi(argv[4]), atoi(argv[5]), argv[6][0]);
        final = lines;
    }
    else {
        cerr << "Unkown operation" << endl;
        return 3;
    }
    //creates file contatining the new grid
    ofstream output;
    output.open(argv[2]);
    for (int i = 0; i < lines.size(); i++) {
        output << final[i] << endl;
    }
    output.close();
    return 0;
}