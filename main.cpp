#include <stdio.h>
#include "renderer.hpp"
#include "vector.hpp"
#include "triangle.hpp"

#define RTS_X 150
#define RTS_Y 150

int main(){
	printf("\n\n\n");
    printf("[+] Welcome to 3DR\n\n");

    Scene s;
    RenderTarget t(RTS_X, RTS_Y);
    Renderer r(Vector(-3,0,0), Vector(1,0,1), 30, &s, &t);
    //Renderer r(Vector(0,0,0), Vector(0,0,1), 30, &s, &t);

    s.lights.push_back(LightSource(Vector(0,0,0), Color(1,1,1)));

    s.triags.push_back(Triangle(
        Vector( 1, 1,-3),
        Vector( 1,-1,-3),
        Vector(-1,-1,-3)
    ));

    s.triags.push_back(Triangle(
        Vector( 1, 1,-3),
        Vector(-1, 1,-3),
        Vector(-1,-1,-3)
    ));

    s.triags.push_back(Triangle(
        Vector( 1, 1, 3),
        Vector( 1,-1, 3),
        Vector(-1,-1, 3)
    ));

    s.triags.push_back(Triangle(
        Vector( 1, 1, 3),
        Vector(-1, 1, 3),
        Vector(-1,-1, 3)
    ));

    s.triags.push_back(Triangle(
        Vector( 1, 1, 5),
        Vector( 1,-1, 5),
        Vector(-1,-1, 5)
    ));

    s.triags.push_back(Triangle(
        Vector( 1, 1, 5),
        Vector(-1, 1, 5),
        Vector(-1,-1, 5)
    ));

    // std::list<Triangle>::iterator i;
    // for(i = s.triags.begin(); i != s.triags.end(); i++){
    //     r.renderTriangle(*i);
    // }

    char c = ' ';
    int x = -3;
    while(c!='0'){
        scanf("%c",&c);
        t.clear();
        r.renderScene();
        r.createView(Vector(--x,0,0), Vector(1,0,1), 30);

        for(int y=RTS_Y-1; y>=0;y--){
            for(int x=0; x<RTS_X; x++){
                printf("%c", t.fb(x,y)?'X':' ');
            }
            printf("\n");
        }
    }

    /*
	Vector a(1,2,3), b(3,2,2);
	printf("%.2f, %.2f, %.2f\n", (a-b)[0], (a-b)[1], (a+b)[2]);
	printf("%.2f, %.2f, %.2f\n", (3*a)[0], (3*a)[1], (3*a)[2]);
	printf("%.2f, %.2f, %.2f\n", (a*3)[0], (a*3)[1], (a*3)[2]);
	printf("%.2f\n", (a*b));
    printf("%.2f\n", ~a);

	printf("\n\n\n");


    //Renderer r(Vector(-2,0,0), Vector(1,0,1), 30);
    Vector v[8];
    Point p;
    v[0] = Vector( 1, 1,3);
    v[1] = Vector( 1,-1,3);
    v[2] = Vector(-1,-1,3);
    v[3] = Vector(-1, 1,3);
    v[4] = Vector( 1, 1,5);
    v[5] = Vector( 1,-1,5);
    v[6] = Vector(-1,-1,5);
    v[7] = Vector(-1, 1,5);

    for(int i=0; i<8; i++){
        //p = r.centralProject(v[i]);
        printf("%.2f, %.2f\n", p.x(), p.y());
    }*/
}
