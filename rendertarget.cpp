#include <stdlib.h>
#include "rendertarget.hpp"


RenderTarget::RenderTarget(int width, int height){
    framebuffer = (uint32_t*)malloc(width*height*sizeof(uint32_t));
    zbuffer = (float*)malloc(width*height*sizeof(float));
    w = width;
    h = height;
}

uint32_t &RenderTarget::fb(int x, int y){
    return this->framebuffer[y*w+x];
}

float &RenderTarget::zb(int x, int y){
    return this->zbuffer[y*w+x];
}

int RenderTarget::width(){
    return w;
}

int RenderTarget::height(){
    return h;
}
