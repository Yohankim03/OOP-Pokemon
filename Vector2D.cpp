#include <iostream>
#include "Vector2D.h"
using namespace std;

Vector2D::Vector2D(){
    x = 0;
    y = 0;
}

Vector2D::Vector2D(double in_x, double in_y){
    x = in_x;
    y = in_y;
}


//  Non-Member Functions
Vector2D operator*(Vector2D v1, double d){
    Vector2D newv((v1.x*d), (v1.y*d));
    return newv;
}

Vector2D operator/(Vector2D v1, double d){
    if (d==0){
        return v1;
    }
    Vector2D newv((v1.x/d), (v1.y/d));
    return newv;
}

ostream& operator<<(ostream& os, Vector2D v1){
    os << "<" << v1.x << "," << v1.y << ">";
    return os;
}

