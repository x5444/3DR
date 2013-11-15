#include "point.hpp"

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

float& Point::dist(){
    return vdist;
}
