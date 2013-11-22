#include "point.hpp"
#include <math.h>

Point::Point(float x, float y, float dist){
    this->vx = x;
    this->vy = y;
    this->vdist = dist;
}

float& Point::x(){
    return vx;
}

float& Point::y(){
    return vy;
}

int Point::xi(){
    return (int)vx;
}

int Point::yi(){
    return (int)vy;
}

float& Point::dist(){
    return vdist;
}

float Point::length(){
    return sqrt(vx*vx+vy*vy);
}

Point Point::scalarMult(float a){
    return Point(a*this->vx, a*this->vy, this->vdist);
}

Point Point::add(Point p){
    return Point(p.vx+this->vx, p.vy+this->vy, p.vdist+this->vdist);
}

Point Point::sub(Point p){
    return Point(this->vx-p.vx, this->vy-p.vy, this->vdist-p.vdist);
}

Point operator*(float a, Point p){
	return p.scalarMult(a);
}

Point operator*(Point p, float a){
	return p.scalarMult(a);
}

Point operator+(Point p1, Point p2){
    return p1.add(p2);
}

Point operator-(Point p1, Point p2){
    return p1.sub(p2);
}
