#ifndef __COLOR_HPP__
#define __COLOR_HPP__

#include <stdint.h>

class Color{
    private:
        uint32_t color;

    public:
        Color(uint32_t c=0);

        Color(uint8_t r, uint8_t g, uint8_t b);

        Color add(Color c);
        
        Color sub(Color c);
        
        Color scalarMult(int a);
};

Color operator+(Color c1, Color c2);

Color operator-(Color c1, Color c2);
    
Color operator*(int a, Color c);

Color operator*(Color c, int a);


#endif //__COLOR_HPP__
