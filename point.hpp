#ifndef __POINT_HPP__
#define __POINT_HPP__

class Point{
    private:
        float vx, vy, vdist;

    public:
        Point(float x=0.0f, float y=0.0f, float dist=0.0f);

        float& x();

        float& y();

        int xi();

        int yi();

        float& dist();

        float length();

        Point scalarMult(float a);

        Point add(Point p);

        Point sub(Point p);
};

Point operator*(float a, Point p);

Point operator*(Point p, float a);

Point operator+(Point p1, Point p2);

Point operator-(Point p1, Point p2);

#endif // __POINT_HPP__
