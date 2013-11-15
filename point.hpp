#ifndef __POINT_HPP__
#define __POINT_HPP__

class Point{
    private:
        float vx, vy, vdist;

    public:
        Point(float x=0.0f, float y=0.0f, float dist=0.0f);

        float& x();

        float& y();

        float& dist();
};

#endif // __POINT_HPP__
