#ifndef _POLYGON_CPP_
#define _POLYGON_CPP_

#include "polygons.h"
using namespace std;

//returns sides of polygon
vector<double> Polygon::getSides(){
    vector<double> sides;
    for (unsigned int i = 0; i < vertices.size()-1; i++){
        sides.push_back(DistanceBetween(vertices[i],vertices[i+1]));
    }
    sides.push_back(DistanceBetween(vertices[vertices.size()-1],vertices[0]));
    return sides;
}
//returns angles of polygon
vector<double> Polygon::getAngles() {
    vector<double> angles;
    for (unsigned int i=0; i < vertices.size()-2; i++){
        angles.push_back(Angle(vertices[i],vertices[i+1],vertices[i+2]));
    }
    angles.push_back(Angle(vertices[vertices.size()-2],vertices[vertices.size()-1],vertices[0]));
    angles.push_back(Angle(vertices[vertices.size()-1],vertices[0],vertices[1]));
    return angles;
}
//checks if all sides are equal
bool Polygon::HasAllEqualSides(){
    vector<double> s = getSides();
    for (unsigned int i = 0; i < s.size()-1; i++){
        if (!EqualSides(s[i],s[i+1])) { return false; }
    }
    if (!EqualSides(s[s.size()-1],s[0])) { return false; }
    return true;
}
//checks if all angles are equal
bool Polygon::HasAllEqualAngles(){
    vector<double> a = getAngles();
    for (unsigned int i = 0; i < a.size()-1; i++){
        if (!EqualAngles(a[i],a[i+1])) { return false; }
    }
    if (!EqualAngles(a[a.size()-1],a[0])) { return false; }
    return true;
}
//checks if any angle is right
bool Polygon::HasARightAngle(){
    vector<double> a = getAngles();
    for (unsigned int i = 0; i < a.size(); i++){
        if (RightAngle(a[i])) { return true; }
    }
    return false;
}
//checks if any angle is obtuse
bool Polygon::HasAnObtuseAngle(){
    vector<double> a = getAngles();
    for (unsigned int i = 0; i < a.size(); i++){
        if (ObtuseAngle(a[i])) { return true; }
    }
    return false;
}
//checks if any angle is acute
bool Polygon::HasAnAcuteAngle(){
    vector<double> a = getAngles();
    for (unsigned int i = 0; i < a.size(); i++){
        if (AcuteAngle(a[i])) { return true; }
    }
    return false;
}
//checks if any angle is reflex (means polygon is concave)
bool Polygon::IsConcave(){
    vector<double> a = getAngles();
    for (unsigned int i = 0; i < a.size(); i++){
        if (ReflexAngle(a[i])) { return true; }
    }
    return false;
}
//if polygon is not concave, it must be convex
bool Polygon::IsConvex(){
    return !IsConcave();
}

#endif