#include "triangle.hpp"

Triangle::Triangle(Vector v1, Vector v2, Vector v3){
    v[0] = v1;
    v[1] = v2;
    v[2] = v3;
    c[0] = Color(1.0f, 0.0f, 0.0f);
    c[1] = Color(1.0f, 0.0f, 0.0f);
    c[2] = Color(1.0f, 0.0f, 0.0f);
    m = (v1+v2+v3)*(1.0f/3.0f);
}

Triangle::Triangle(Vector v1, Color c1, Vector v2, Color c2, Vector v3, Color c3){
    v[0] = v1;
    c[0] = c1;
    v[1] = v2;
    c[1] = c2;
    v[2] = v3;
    c[2] = c3;
    m = (v1+v2+v3)*(1.0f/3.0f);
}

void Triangle::buildNormal(Vector ref){
    Vector v1 = v[0]-v[1];
    Vector v2 = v[2]-v[1];
    n = (v1%v2).normalize();

    if( n*(m-ref) < 0 ){
        n = -1*n;
    }
}

Vector Triangle::normal(){
    return n;
}

Vector Triangle::middle(){
    return m;
}
