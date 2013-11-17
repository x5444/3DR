#ifndef __RENDERTARGET_HPP__
#define __RENDERTARGET_HPP__

#include <stdint.h>

class RenderTarget{
    private:
        uint32_t *framebuffer;
        float *zbuffer;
        int w, h;

    public:
        RenderTarget(int width, int height);

        int width();
        int height();

        uint32_t &fb(int x, int y);
        float &zb(int x, int y);
};

#endif // __RENDERTARGET_HPP__
