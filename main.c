#include <stdio.h>
#include <stdint.h>
#include <math.h>

struct Vertex{
    float x;
    float y;
    float z;

    float  dist;
};

struct Triangle{
    struct Vertex v1;
    struct Vertex v2;
    struct Vertex v3;

    uint32_t color;
};

struct Point{
    float x;
    float y;
};

struct PointInt{
    uint16_t x;
    uint16_t y;
};

#define TRIANGLE_LIST_LEN 100
#define SIZE_X 2
#define SIZE_Y 2
#define RES_X 800
#define RES_Y 600
#define SCALE_X 170
#define SCALE_Y 100
#define PI 3.1415

struct Triangle triangleList[TRIANGLE_LIST_LEN]; //make me an actual list
struct Vertex eyePoint;
struct Vertex mainPoint;
struct Vertex n0, e1, e2;
float d = 0;

uint32_t frameBuffer[RES_X][RES_Y];
float zBuffer[RES_X][RES_Y];

struct Triangle *getNextTriangle(){
    static int i=0;
    return &triangleList[i++];
}

void pushTriangle(struct Triangle t){
    //float xb = t->x - x;      DO SOME DEPTH MAPPING OR SOMETHING
    //float yb = t->y - y;      TODO
    //float zb = t->z - z;
    //float dist = sqrt(xb*xb + yb*yb + zb*zb); //naive

    //int i;
    //for(i=0; i<TRIANGLE_LIST_LEN; i++){
    //    if(triangleList[i].dist >= dist){
    //        break;
    //    }
    //}

    //for(int j=TRIANGLE_LIST_LEN; j>i; j--){
    //    triangleList[j] = triangleList[j-1];
    //}
    //triangleList[i] = *t;

    static int i=0;
    triangleList[i++] = t;
}

void restartTriangleList(){
}

struct Vertex vadd(struct Vertex v1, struct Vertex v2){
    struct Vertex res;
    res.x = v1.x + v2.x;
    res.y = v1.y + v2.y;
    res.z = v1.z + v2.z;
    return res;
}

struct Vertex vsub(struct Vertex v1, struct Vertex v2){
    struct Vertex res;
    res.x = v1.x - v2.x;
    res.y = v1.y - v2.y;
    res.z = v1.z - v2.z;
    return res;
}

struct Vertex smul(float x, struct Vertex v){
    struct Vertex res;
    res.x = v.x *x;
    res.y = v.y *x;
    res.z = v.z *x;
    return res;
}

float sprod(struct Vertex v1, struct Vertex v2){
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

struct Vertex vprod(struct Vertex v1, struct Vertex v2){
    struct Vertex res;
    res.x = v1.y*v2.z - v1.z*v2.y;
    res.y = v1.z*v2.x - v1.x*v2.z;
    res.z = v1.x*v2.y - v1.y*v2.x;
    return res;
}

float vlen(struct Vertex v){
    return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

struct Vertex p(float x, float y, float z){
    struct Vertex res;
    res.x = x;
    res.y = y;
    res.z = z;
    return res;
}

struct Triangle t(struct Vertex v1, struct Vertex v2, struct Vertex v3){
    struct Triangle res;
    res.v1 = v1;
    res.v2 = v2;
    res.v3 = v3;
    return res;
}


void generateView(struct Vertex eye, struct Vertex dir, float angle){ //dir should probably be a vector of angles or something
    d = ((SIZE_X)/2)/tan((angle*PI)/180);
    struct Vertex nns = smul(d, dir);
    mainPoint = vadd(nns, eye);
    eyePoint = eye;
    n0 = dir;
    if(n0.y==0){
        e1 = p(1,0,0);
    }else{
        e1.y = 1;
        e1.x = (n0.y/n0.x)*e1.y;
        e1 = smul((1/vlen(e1)),e1);
    }
    e2 = vprod(e1, n0);
}

struct Point transform(struct Vertex *v){
    float xn = sprod(vsub(*v, mainPoint), e1);
    float yn = sprod(vsub(*v, mainPoint), e2);
    float zn = sprod(vsub(*v, mainPoint), n0);
    struct Point res;
    res.x = xn/(1-(zn/d));
    res.y = yn/(1-(zn/d));

    v->dist = vlen(vsub(*v, eyePoint));
    return res;
}

int main(){
    printf("\n\nWelcome\n\n");

    generateView(p(-2,2,0), p(0,0,1), 35);

    printf("View:\n");
    printf("%.3f\n", d);
    printf("n0 = (%.3f, %.3f, %.3f)\n", n0.x, n0.y, n0.z);
    printf("e1 = (%.3f, %.3f, %.3f)\n", e1.x, e1.y, e1.z);
    printf("e2 = (%.3f, %.3f, %.3f)\n", e2.x, e2.y, e2.z);
    printf("ep = (%.3f, %.3f, %.3f)\n", eyePoint.x, eyePoint.y, eyePoint.z);
    printf("mp = (%.3f, %.3f, %.3f)\n", mainPoint.x, mainPoint.y, mainPoint.z);

    pushTriangle(t(p(-1,-1,5), p(-1,1,5), p(1,1,5)));
    pushTriangle(t(p(-1,-1,5), p(1,-1,5), p(1,1,5)));

    pushTriangle(t(p(-1,-1,4), p(-1,1,4), p(1,1,4)));
    pushTriangle(t(p(-1,-1,4), p(1,-1,4), p(1,1,4)));


    for(int i=0; i<4; i++){
        struct Triangle tr = *getNextTriangle();

        struct Point pn1 = transform(&(tr.v1));
        struct PointInt pi[3];
        pi[0].x = (uint16_t)(pn1.x)*SCALE_X + (RES_X/2);
        pi[0].y = (uint16_t)(pn1.y)*SCALE_Y + (RES_Y/2);
        printf("%.3f,%.3f\n", pn1.x, pn1.y);

        struct Point pn2 = transform(&(tr.v2));
        struct PointInt pi2;
        pi[1].x = (uint16_t)(pn2.x)*SCALE_X + (RES_X/2);
        pi[1].y = (uint16_t)(pn2.y)*SCALE_Y + (RES_Y/2);
        printf("%.3f,%.3f\n", pn2.x, pn2.y);

        struct Point pn3 = transform(&(tr.v3));
        struct PointInt pi3;
        pi[2].x = (uint16_t)(pn3.x)*SCALE_X + (RES_X/2);
        pi[2].y = (uint16_t)(pn3.y)*SCALE_Y + (RES_Y/2);
        printf("%.3f,%.3f\n", pn3.x, pn3.y);

        //sort points by y coordinate
        struct PointInt pib;
        if(pi[0].y > pi[1].y){
            pib = pi[0];
            pi[0] = pi[1];
            pi[1] = pib;
        }
        if(pi[1].y > pi[2].y){
            pib = pi[1];
            pi[1] = pi[2];
            pi[2] = pib;
        }
        if(pi[0].y > pi[1].y){
            pib = pi[0];
            pi[0] = pi[1];
            pi[1] = pib;
        }

        

    }

    return 0;
}
