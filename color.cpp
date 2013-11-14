#include "color.hpp"

Color::Color(){
    this->color = 0xFFFFFFFF;
}

Color::Color(uint32_t c){
    this->color = c;
}

Color::Color(uint8_t r, uint8_t g, uint8_t b){
    this->color = (uint32_t)r<<24 | (uint32_t)g<<16 | (uint32_t)b<<8;
}

