#ifndef Vector2D
#define Vector2D

#include <stdio.h>
#include <math.h>

class Vector2D
{
public:
    double x, y;
    Vector2D(double x,double y) {this->x = x, this->y = y; }              //initializes the vector
    Vector2D() { this->x = this->y = 0; }                                   //initializes the zero vector
    Vector2D polar(double r, double t) { return {r * cos(t), r * sin(t)}; } //creates a vector

    Vector2D operator+(Vector2D ot) { return {this->x + ot.x, this->y + ot.y}; } //adding two
    Vector2D operator-(Vector2D ot) { return {this->x - ot.x, this->y - ot.y}; } //subtracting
    double dot(Vector2D ot) { return this->x * ot.x + this->y * ot.y; }          //returns the dotproduct
    double cross(Vector2D ot) { return this->x * ot.y - this->y * ot.x; }        //returns the 2D
    double mag() { return sqrt(this->x * this->x + this->y * this->y); }         //returns the
    double dir() { return atan2(this->y, this->x); }                             //returns the direction the vector is

    Vector2D norm()
    {
        double t = dir();
        return {cos(t), sin(t)};
    } 

    Vector2D operator*(double c) { return {this->x * c, this->y * c}; } 

    Vector2D
    operator/(double c) { return {this->x / c, this->y / c}; } 
    double proj(Vector2D ot) { return this->dot(ot) / ot.mag(); }

    Vector2D perp() { return {-y, x}; } 
};
#endif