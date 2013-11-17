#ifndef __LIGHTSOURCE_HPP__
#define __LIGHTSOURCE_HPP__

#include "vector.hpp"
#include "color.hpp"

class LightSource{
    public:
        LightSource();
        LightSource(Vector p, Color c);

        Vector pos;
        Color intensity;
};

#endif // __LIGHTSOURCE_HPP__
