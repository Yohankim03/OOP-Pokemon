#ifndef Vector2D_H
#define Vector2D_H

#include <iostream>
#include "Point2D.h"
using namespace std;

class Point2D;

class Vector2D{
    public:
        double x;
        double y;

        Vector2D();
        Vector2D(double, double);
};

Vector2D operator*(Vector2D, double);

Vector2D operator/(Vector2D, double);

ostream& operator<<(ostream&, Vector2D);
    

#endif
