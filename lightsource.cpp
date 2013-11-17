#include "lightsource.hpp"

LightSource::LightSource(){
    this->pos = Vector(0,0,0);
    this->intensity = Color();
}

LightSource::LightSource(Vector p, Color c){
    this->pos = p;
    this->intensity = c;
}
