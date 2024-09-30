#include <iostream>
#include <math.h>
#include "Point2D.h"
using namespace std;

Point2D::Point2D(){
    x = 0;
    y = 0;
}


Point2D::Point2D(double in_x, double in_y){
    x = in_x;
    y = in_y;
}

double GetDistanceBetween(Point2D p1, Point2D p2){
    double distanceX = pow((p2.x - p1.x), 2);
    double distanceY = pow((p2.y - p1.y), 2);
    double distance  = sqrt(distanceX + distanceY);
    return distance;
}

//  Non-Member Functions
ostream& operator<<(ostream& os, Point2D p1){
    os << "(" << p1.x << "," << p1.y << ")";
    return os;
}

Point2D operator+(Point2D p1, Vector2D v1){
    Point2D newp((p1.x+v1.x), (p1.y+v1.y));
    return newp;
}

Vector2D operator-(Point2D p1, Point2D p2){
    Vector2D newv((p1.x-p2.x), (p1.y-p2.y));
    return newv;
}

bool operator==(Point2D p1, Point2D p2){
    if ((p1.x == p2.x) && (p1.y == p2.y))
        return true;
    else return false;
}