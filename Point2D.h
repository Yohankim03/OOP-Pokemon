#ifndef Point2D_H
#define Point2D_H

#include <iostream>
#include "Vector2D.h"
using namespace std;

class Vector2D;

class Point2D{
    public:
        double x;
        double y;

        Point2D();
        Point2D(double, double);

};

double GetDistanceBetween(Point2D, Point2D);

ostream& operator<<(ostream&, Point2D);

Point2D operator+(Point2D, Vector2D);

Vector2D operator-(Point2D, Point2D);

bool operator==(Point2D, Point2D);

#endif