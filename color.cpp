#include "color.hpp"


Color::Color(){
    this->c[0] = 0;
    this->c[1] = 0;
    this->c[2] = 0;
}

Color::Color(float r, float g, float b){
    this->c[0] = r;
    this->c[1] = g;
    this->c[2] = b;
}

uint32_t Color::toInt(){
    return ((uint32_t)(this->c[0]*255)&0xFF)<<16 | ((uint32_t)(this->c[1]*255)&0xFF)<<8 | ((uint32_t)(this->c[2]*255)&0xFF);
}

Color Color::add(Color c){
    return Color(this->c[0] + c.r(), this->c[1] + c.g(), this->c[2] + c.b());
}

Color Color::sub(Color c){
    return Color(this->c[0] - c.r(), this->c[1] - c.g(), this->c[2] - c.b());
}

Color Color::scalarMult(float a){
    return Color(this->c[0]*a, this->c[1]*a, this->c[2]*a);
}

Color Color::scalarProd(Color c1){
    return Color(this->c[0]*c1.c[0], this->c[1]*c1.c[1], this->c[2]*c1.c[2]);
}


float &Color::r(){
    return this->c[0];
}

float &Color::g(){
    return this->c[1];
}

float &Color::b(){
    return this->c[2];
}


Color operator+(Color c1, Color c2){
    return c1.add(c2);
}

Color operator-(Color c1, Color c2){
    return c1.sub(c2);
}
    
Color operator*(float a, Color c){
	return c.scalarMult(a);
}

Color operator*(Color c, float a){
	return c.scalarMult(a);
}

Color operator*(Color c1, Color c2){
	return c1.scalarProd(c2);
}
