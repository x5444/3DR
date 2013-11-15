#include "color.hpp"


Color::Color(uint32_t c){
    this->color = c;
}

Color::Color(uint8_t r, uint8_t g, uint8_t b){
    this->color = (uint32_t)r<<24 | (uint32_t)g<<16 | (uint32_t)b<<8;
}

Color Color::add(Color c){
    return Color(this->color + c.color);
}

Color Color::sub(Color c){
    return Color(this->color - c.color);
}

Color Color::scalarMult(int a){
    return Color(this->color * a);
}

Color operator+(Color c1, Color c2){
    return c1.add(c2);
}

Color operator-(Color c1, Color c2){
    return c1.sub(c2);
}
    
Color operator*(int a, Color c){
	return c.scalarMult(a);
}

Color operator*(Color c, int a){
	return c.scalarMult(a);
}

