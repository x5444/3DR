#ifndef __RENDERTARGET_HPP__
#define __RENDERTARGET_HPP__

#include <stdint.h>

class RenderTarget{
    private:
        float *zbuffer;
        int w, h;
        uint32_t *framebuffer;

    public:
        RenderTarget(int width, int height);

        void clear();

        int width();
        int height();

        uint32_t &fb(int x, int y);
        uint32_t *fbadr();
        void setfb(int x, int y, uint32_t val);
        float &zb(int x, int y);
        float *zbadr();
};

#endif // __RENDERTARGET_HPP__
