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
    Renderer r(Vector(3,3,0), Vector(-1,-1,1), 30, &s, &t);
    //Renderer r(Vector(0,0,0), Vector(0,0,1), 30, &s, &t);

    s.lights.push_back(LightSource(Vector(0,0,0), Color(1,1,1)));

    //s.triags.push_back(Triangle(
    //    Vector( 1, 1,-3),
    //    Vector( 1,-1,-3),
    //    Vector(-1,-1,-3)
    //));

    //s.triags.push_back(Triangle(
    //    Vector( 1, 1,-3),
    //    Vector(-1, 1,-3),
    //    Vector(-1,-1,-3)
    //));

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

    int x = 6;
    char c='-';
    while(1){
        t.clear();
        r.renderScene();
        r.createView(Vector((float)x/2,3,0), Vector((float)x*(-1.0f/6.0f),-1,1), 30);

        if(x==-20){
            c='+';
        }else if(x==20){
            c='-';
        }

        if(c=='+'){
            x++;
        }else if(c=='-'){
            x--;
        }

        for(int y=RTS_Y-1; y>=0;y--){
            for(int x=0; x<RTS_X; x++){
                printf("%c", t.fb(x,y)?'X':' ');
            }
            printf("\n");
        }
    }
}
