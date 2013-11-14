#ifndef __COLOR_HPP__
#define __COLOR_HPP__

#include <stdint.h>

class Color{
    private:
        uint32_t color;

    public:
        Color();
        Color(uint32_t c);
        Color(uint8_t r, uint8_t g, uint8_t b);
};

#endif //__COLOR_HPP__
