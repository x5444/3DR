#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "rendertarget.hpp"


RenderTarget::RenderTarget(int width, int height){
    framebuffer = (uint32_t*)malloc(width*height*sizeof(uint32_t));
    zbuffer = (float*)malloc(width*height*sizeof(float));

    w = width;
    h = height;

    this->clear();
}

void RenderTarget::clear(){
    for(int i=0; i<w*h; i++){
        framebuffer[i]=0;
        zbuffer[i] = 1000;
    }
}

uint32_t zero = 0;
uint32_t &RenderTarget::fb(int x, int y){
    zero = 0;
    if(x<w && y<h && x>=0 && y>=0){
        return this->framebuffer[((h-y-1)*w)+x];
    }else{
        return zero;
    }
}

void RenderTarget::setfb(int x, int y, uint32_t val){
        this->framebuffer[((h-y-1)*w)+x] = val;
}

float zerof = 0;
float &RenderTarget::zb(int x, int y){
    zero = 0;
    if(x<w && y<h && x>=0 && y>=0){
        return this->zbuffer[y*w+x];
    }else{
        return zerof;
    }
}

uint32_t *RenderTarget::fbadr(){
    return framebuffer;
}

int RenderTarget::width(){
    return w;
}

int RenderTarget::height(){
    return h;
}
