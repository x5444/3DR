#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include <list>

#include "lightsource.hpp"
#include "triangle.hpp"

class Scene{
    public:
        std::list<LightSource> lights;
        std::list<Triangle> triags;

        LightSource globalBr;
};

#endif // __SCENE_HPP__
