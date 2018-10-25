#ifndef _POLYGON_H_
#define _POLYGON_H_

#include <iostream>
#include <vector>
#include "utilities.h"
using namespace std;

//Polygon
class Polygon{
public:
    Polygon(const string &n, const vector<Point> &v): name(n), vertices(v) {}
    virtual ~Polygon() {}
    string getName() { return name;}
    int NumVerts() { return vertices.size(); }
    vector<double> getSides();
    vector<double> getAngles();
    virtual bool HasAllEqualSides();
    virtual bool HasAllEqualAngles();
    virtual bool HasARightAngle();
    virtual bool HasAnObtuseAngle();
    virtual bool HasAnAcuteAngle();
    virtual bool IsConcave();
    virtual bool IsConvex();
protected:
    string name;
    vector<Point> vertices;
};
//Triangle
class Triangle: public Polygon{
public:
    Triangle(const string &n, const vector<Point> &v): Polygon(n,v){
        //has 3 vertices
        if (v.size() != 3) { throw 0; }
    }
    bool HasAnAcuteAngle() { return true; }
    bool IsConcave() { return false; }
    bool IsConvex() { return true; }
};
//Obtuse Triangle
class ObtuseTriangle: virtual public Triangle{
public:
    ObtuseTriangle(const string &n, const vector<Point> &v): Triangle(n,v){
        //has an obtuse angle
        if (!Polygon::HasAnObtuseAngle()) { throw 0; }
    }
    bool HasAllEqualSides() { return false; }
    bool HasAllEqualAngles() { return false; }
    bool HasARightAngle() { return false; }
    bool HasAnObtuseAngle() { return true; }
};
//Isosceles Triangle
class IsoscelesTriangle: virtual public Triangle{
public:
    IsoscelesTriangle(const string &n, const vector<Point> &v): Triangle(n,v){
        //has at least 2 equal angles
        double a1 = Angle(v[0],v[1],v[2]);
        double a2 = Angle(v[1],v[2],v[0]);
        double a3 = Angle(v[2],v[0],v[1]);
        if (!EqualAngles(a1,a2) and !EqualAngles(a2,a3) and !EqualAngles(a3,a1)) { throw 0; }
    }
};
//Right Triangle
class RightTriangle: virtual public Triangle{
public:
    RightTriangle(const string &n, const vector<Point> &v): Triangle(n,v){
        //has a right angle
        if (!Polygon::HasARightAngle()) { throw 0; }
    }
    bool HasAllEqualSides() { return false; }
    bool HasAllEqualAngles() { return false; }
    bool HasARightAngle() { return true; }
    bool HasAnObtuseAngle() { return false; }
};
//Isosceles Obtuse Triangle
class IsoscelesObtuseTriangle: public ObtuseTriangle, public IsoscelesTriangle{
public:
    IsoscelesObtuseTriangle(const string &n, const vector<Point> &v): Triangle(n,v), ObtuseTriangle(n,v), IsoscelesTriangle(n,v) {}
};
//Equilateral Triangle
class EquilateralTriangle: public IsoscelesTriangle{
public:
    EquilateralTriangle(const string &n, const vector<Point> &v): Triangle(n,v), IsoscelesTriangle(n,v){
        //has all equal angles
        if (!Polygon::HasAllEqualAngles()) { throw 0; }
    }
    bool HasAllEqualSides() { return true; }
    bool HasAllEqualAngles() { return true; }
    bool HasARightAngle() { return false; }
    bool HasAnObtuseAngle() { return false; }
};
//Isosceles Right Triangle
class IsoscelesRightTriangle: public IsoscelesTriangle, public RightTriangle{
public:
    IsoscelesRightTriangle(const string &n, const vector<Point> &v): Triangle(n,v), IsoscelesTriangle(n,v), RightTriangle(n,v) {}
};
//Quadrilateral
class Quadrilateral: public Polygon{
public:
    Quadrilateral(const string &n, const vector<Point> &v): Polygon(n,v){
        //has 4 vertices
        if (v.size() != 4) { throw 0; }
    }
};
//Trapezoid
class Trapezoid: virtual public Quadrilateral{
public:
    Trapezoid(const string &n, const vector<Point> &v): Quadrilateral(n,v){
        //has at least 1 set of parallel sides
        Vector v1(v[0],v[1]);
        Vector v2(v[1],v[2]);
        Vector v3(v[2],v[3]);
        Vector v4(v[3],v[0]);
        if (!Parallel(v1,v3) and !Parallel(v2,v4)) { throw 0; }
    }
    bool isConcave() { return false; }
    bool isConvex() { return true; }
};
//Kite
class Kite: virtual public Quadrilateral{
public:
    Kite(const string &n, const vector<Point> &v): Quadrilateral(n,v){
        //has 2 sets of equal sides and is concave
        double s1 = DistanceBetween(v[0],v[1]);
        double s2 = DistanceBetween(v[1],v[2]);
        double s3 = DistanceBetween(v[2],v[3]);
        double s4 = DistanceBetween(v[3],v[0]);
        if (!(EqualSides(s1,s2) and EqualSides(s3,s4)) and !(EqualSides(s2,s3) and EqualSides(s4,s1))) { throw 0; }
        if (Polygon::IsConcave()) { throw 0; }
    }
    bool IsConcave() { return false; }
    bool IsConvex() { return true; }
};
//Arrow
class Arrow: public Quadrilateral{
public:
    Arrow(const string &n, const vector<Point> &v): Quadrilateral(n,v){
        //has 2 sets of equal sides and is convex
        double s1 = DistanceBetween(v[0],v[1]);
        double s2 = DistanceBetween(v[1],v[2]);
        double s3 = DistanceBetween(v[2],v[3]);
        double s4 = DistanceBetween(v[3],v[0]);
        if (!(EqualSides(s1,s2) and EqualSides(s3,s4)) and !(EqualSides(s2,s3) and EqualSides(s4,s1))) { throw 0; }
        if (!Polygon::IsConcave()) { throw 0; }
    }
    bool HasAllEqualSides() { return false; }
    bool HasAllEqualAngles() { return false; }
    bool HasAnAcuteAngle() { return true; }
    bool IsConcave() { return true; }
    bool IsConvex() { return false; }
};
//Isosceles Trapezoid
class IsoscelesTrapezoid: virtual public Trapezoid{
public:
    IsoscelesTrapezoid(const string &n, const vector<Point> &v): Quadrilateral(n,v), Trapezoid(n,v){
        //base of trapezoid must have equal angles
        Vector v1(v[0],v[1]);
        Vector v3(v[2],v[3]);
        double a2 = Angle(v[1],v[2],v[3]);
        double a3 = Angle(v[2],v[3],v[0]);
        double a4 = Angle(v[3],v[0],v[1]);
        if (Parallel(v1,v3)){
            if (!EqualAngles(a2,a3)) { throw 0; }
        }
        else{
            if (!EqualAngles(a3,a4)) { throw 0; }
        }
    }
};
//Parallelogram
class Parallelogram: virtual public Trapezoid{
public:
    Parallelogram(const string &n, const vector<Point> &v): Quadrilateral(n,v), Trapezoid(n,v){
        //has 2 sets of parallel sides
        Vector v1(v[0],v[1]);
        Vector v2(v[1],v[2]);
        Vector v3(v[2],v[3]);
        Vector v4(v[3],v[0]);
        if (!Parallel(v1,v3) or !Parallel(v2,v4)) { throw 0; }
    }
};
//Rectangle
class Rectangle: public IsoscelesTrapezoid, virtual public Parallelogram{
public:
    Rectangle(const string &n, const vector<Point> &v): Quadrilateral(n,v), Trapezoid(n,v), Parallelogram(n,v), IsoscelesTrapezoid(n,v){
        //has all right angles
        if (!(Polygon::HasARightAngle() and Polygon::HasAllEqualAngles())) { throw 0; }
    }
    bool HasAllEqualAngles() { return true; }
    bool HasARightAngle() { return true; }
    bool HasAnObtuseAngle() { return false; }
    bool HasAnAcuteAngle() { return false; }
};
//Rhombus
class Rhombus: public Kite, virtual public Parallelogram{
public:
    Rhombus(const string &n, const vector<Point> &v): Quadrilateral(n,v), Trapezoid(n,v), Parallelogram(n,v), Kite(n,v){
        //has all equal sides
        if (!Polygon::HasAllEqualSides()) { throw 0; }
    }
    bool HasAllEqualSides() { return true; }
};
//Square
class Square: public Rectangle, public Rhombus{
public:
    Square(const string &n, const vector<Point> &v): Quadrilateral(n,v), Trapezoid(n,v), Parallelogram(n,v), Rectangle(n,v), Rhombus(n,v) {}
};

#endif