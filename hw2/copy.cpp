//
//  main.cpp
//  Homework 2
//
//  Created by Jerry Jacobs on 2/8/16.
//  Copyright © 2016 Jerry Jacobs. All rights reserved.
//

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

int main(){
    int width = 5;
    int *heights;
    heights = new int[width];
    for (int i = 0; i < width; i++){
        heights[i] = i;
    }
    for (int i = 0; i < width; i++){
        cout << heights[i] << endl;
    }
    
    heights[1] = 9;
    
    int max = 0;
    for (unsigned int i = 0; i < width; i++){
        if (heights[i] > max){
            max = heights[i];
        }
    }
    cout << max << endl;
}