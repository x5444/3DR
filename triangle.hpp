#ifndef __TRIANGLE_HPP__
#define __TRIANGLE_HPP__

#include "vector.hpp"
#include "color.hpp"

class Triangle{
    private:
        Vector v[3];    // 3 Corners
        Color c[3];     // With a color each
        Vector n;       // 1 Normal
        Vector m;       // Middle

    public:
        Triangle(Vector v1, Vector v2, Vector v3);
        Triangle(Vector v1, Color c1, Vector v2, Color c2, Vector v3, Color c3);

        void buildNormal(Vector ref);   // This needs a reference point in order to
                                        // correctly align the normal. It'll point
                                        // away from the reference point.

        Vector normal();

        Vector middle();
};

#endif // __TRIANGLE_HPP__
