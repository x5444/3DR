#ifndef __COLOR_HPP__
#define __COLOR_HPP__

#include <stdint.h>

class Color{
    private:
        float c[3];

    public:
        Color();

        Color(float r, float g, float b);

        Color add(Color c);
        
        Color sub(Color c);
        
        Color scalarMult(float a);

        Color scalarProd(Color c1);

        uint32_t toInt();

        float &r();
        float &g();
        float &b();
};

Color operator+(Color c1, Color c2);

Color operator-(Color c1, Color c2);
    
Color operator*(float a, Color c);

Color operator*(Color c, float a);

Color operator*(Color c1, Color c2);


#endif //__COLOR_HPP__
